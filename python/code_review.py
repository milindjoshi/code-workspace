import ollama
import os
import sys

def analyze_code():
    print("--- 🛠️ AI Code Reviewer (Fast-Phi or Qwen2.5-Coder) ---")
    file_path = input("Enter the path to your .java or .cpp file: ").strip()
    
    # Expand ~ to full path and check if file exists
    full_path = os.path.expanduser(file_path)
    if not os.path.exists(full_path):
        print(f"❌ Error: File not found at {full_path}")
        return

    try:
        with open(full_path, 'r') as f:
            code_content = f.read()
    except Exception as e:
        print(f"❌ Error reading file: {e}")
        return

    print(f"\n📄 Analyzing {os.path.basename(file_path)}...")
    print("AI Analysis: ", end="")
    sys.stdout.flush()

    # System instruction to focus the AI
    prompt = f"""
    You are an expert Senior Software Engineer. 
    Review the following code and provide:
    1. A brief 2-sentence summary of what it does.
    2. Any potential bugs or logic errors.
    3. One suggestion for better performance.

    CODE:
    {code_content}
    """

    try:
        stream = ollama.chat(
#            model='fast-phi',
            model='qwen2.5-coder:1.5b',
            messages=[{'role': 'user', 'content': prompt}],
            stream=True,
        )
        
        for chunk in stream:
            print(chunk['message']['content'], end="")
            sys.stdout.flush()
        print("\n" + "-"*40)
            
    except Exception as e:
        print(f"\n❌ AI Error: {e}")

if __name__ == "__main__":
    analyze_code()
