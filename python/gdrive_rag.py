import os
import json
import subprocess
import docx # Ensure you ran 'pip install python-docx'
from dotenv import load_dotenv


# Load the variables from your local .env file
load_dotenv()

# --- CONFIGURATION (Now using Generic Keys) ---
# os.getenv('KEY', 'Default') pulls from .env or uses the backup if missing
SOURCE_DIR = os.getenv("GDRIVE_PATH", "./default_drive")
INDEX_FILE = os.getenv("INDEX_FILENAME", "default_index.json")

def extract_text(path):
    """Reuse your robust extraction logic."""
    try:
        if path.endswith('.docx'):
            doc = docx.Document(path)
            return "\n".join([p.text for p in doc.paragraphs])
        with open(path, 'r', encoding='utf-8') as f:
            return f.read()
    except Exception as e:
        return ""

def build_index():
    """Step 1: Scan GDrive and save text to a local JSON file."""
    print("indexing Google Drive... (this may take a minute)")
    data = []
    for root, _, files in os.walk(SOURCE_DIR):
        for file in files:
            if file.endswith((".txt", ".docx")):
                full_path = os.path.join(root, file)
                content = extract_text(full_path)
                if content.strip():
                    data.append({"filename": file, "content": content})
    
    with open(INDEX_FILE, "w") as f:
        json.dump(data, f)
    print(f"✅ Indexed {len(data)} documents.")

def ask_rag(question):
    """Step 2: Find relevant snippets and ask the SLM."""
    if not os.path.exists(INDEX_FILE):
        build_index()

    with open(INDEX_FILE, "r") as f:
        index = json.load(f)

    # Simple Retrieval: Find files that share keywords with the question
    keywords = question.lower().split()
    context_chunks = []
    
    for doc in index:
        # If any keyword matches, grab a snippet of that document
        if any(key in doc['content'].lower() for key in keywords):
            # Take the first 1500 chars to stay within SLM memory limits
            context_chunks.append(f"--- From {doc['filename']} ---\n{doc['content'][:1500]}")

    context_text = "\n\n".join(context_chunks[:3]) # Only give it top 3 matches

    if not context_text:
        print("No relevant documents found.")
        return

    # Final Step: Feed context to Qwen
    prompt = f"""You are a helpful assistant. Use the following document snippets to answer the user's question. 
    If the answer isn't in the context, say you don't know.

    CONTEXT:
    {context_text}

    QUESTION: {question}"""

    print("\n🤖 Qwen is thinking...")
    result = subprocess.run(
        ['ollama', 'run', 'qwen2.5-coder:1.5b', prompt],
        capture_output=True, text=True
    )
    return result.stdout.strip()
#    print("\n" + "="*20 + "\n" + result.stdout + "\n" + "="*20)

# --- EXECUTION ---
if __name__ == "__main__":
    # You can rebuild the index once a day or whenever GDrive changes
    print("--- GDrive RAG System ---")

    # Check if we need to build or update
    choice = input("Do you want to (1) Ask a question or (2) Rebuild the index? [1/2]: ")

    if choice == "2" or not os.path.exists(INDEX_FILE):
        # You could even ask for a specific sub-folder here:
        # sub = input("Enter sub-folder name (blank for root): ")
        # SOURCE_DIR = os.path.join(os.path.expanduser("~/gdrive"), sub)
        build_index()
    
    # 2. Start the Continuous Loop
    while True:
        user_input = input("\n💬 Query: ").strip()

        # Exit condition
        if user_input.lower() in ['exit', 'quit', 'q']:
            print("\n👋 Shutting down... Goodbye!")
            break

        # Ignore accidental empty enters
        if not user_input:
            continue

        # Get and display the answer
        answer = ask_rag(user_input)
        print("\n🤖 ANSWER:")
        print("-" * 20)
        print(answer)
        print("-" * 20)
