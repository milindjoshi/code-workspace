import ollama
import os

def analyze_document():
    path = input("Enter the path to the text file: ").strip()
    full_path = os.path.expanduser(path)

    if not os.path.exists(full_path):
        print("❌ File not found.")
        return

    with open(full_path, 'r') as f:
        content = f.read()

    # Limit content length to avoid hitting your 2048 token limit in fast-phi
    content_snippet = content[:4000] 

    prompt = f"""
    Analyze the following text:
    1. Summarize it in 3 bullet points.
    2. Determine the overall sentiment (Positive, Negative, or Neutral).
    3. Identify the 3 most important keywords.

    TEXT:
    {content_snippet}
    """

    print("\n🔍 Analyzing...")
    
    # We use 'phi3' or 'fast-phi' here
    response = ollama.chat(model='fast-phi', messages=[
        {'role': 'user', 'content': prompt}
    ])

    print("\n--- ANALYSIS RESULTS ---")
    print(response['message']['content'])

if __name__ == "__main__":
    analyze_document()
