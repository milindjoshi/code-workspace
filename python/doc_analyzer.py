import os
import docx  # The library we just installed
import re
import subprocess

def get_text_from_file(path):
    """Detects file type and extracts plain text."""
    if path.lower().endswith('.docx'):
        # Extract text from Word paragraphs
        doc = docx.Document(path)
        return "\n".join([para.text for para in doc.paragraphs])
    else:
        # Standard text file reading
        with open(path, 'r', encoding='utf-8') as f:
            return f.read()

def analyze_document():
    path_input = input("Enter the path to the file: ").strip().replace("\\ ", " ")
    file_path = os.path.expanduser(path_input)

    if not os.path.exists(file_path):
        print(f"❌ File not found: {file_path}")
        return

    # Extract the text
    text = get_text_from_file(file_path)

    if not text.strip():
        print("❌ Could not extract any text. The file might be empty or corrupted.")
        return

    # --- PART A: Word Count & Keywords ---
    words = re.findall(r'\w+', text.lower())
    print(f"\n📊 Word Count: {len(words)}")
    
    keywords = ["deadline", "payment", "video"]
    found = {k: text.lower().count(k) for k in keywords}
    print(f"🔍 Keywords: {found}")

    # --- PART B: SLM Analysis ---
    print("\n🤖 Sending to Qwen for summary...")
    prompt = f"Summarize this Statement of Work and list 3 key deadlines:\n\n{text[:3000]}"
    
    result = subprocess.run(
        ['ollama', 'run', 'qwen2.5-coder:1.5b', prompt],
        capture_output=True, text=True
    )
    print("\n📝 SLM SUMMARY:\n", result.stdout)

if __name__ == "__main__":
    analyze_document()
