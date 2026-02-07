import ollama
import sys
import os

def run_sh_assistant():
    print("--- ⌨️ AI Shell Assistant (Persistent Mode) ---")
    print("Type 'exit' or 'quit' to stop.\n")
    
    # Pre-define a safety prompt to keep the AI focused on the home/workspace
    system_rules = (
        "You are a Linux command assistant. "
        "Rule 1: Always suggest commands that target the current directory (.) or ~/ unless specified. "
        "Rule 2: Never suggest scanning the root (/) directory. "
        "Rule 3: If a search is requested, add 'timeout 10s' to the start of the command to prevent VM freezes."
    )

    while True:
        user_req = input("Prompt: ")
        
        if user_req.lower() in ['exit', 'quit']:
            print("Goodbye!")
            break

        if not user_req.strip():
            continue

        print("Generating command...", end="\r")
        
        try:
            # We use the chat method to keep the system rules in context
            response = ollama.chat(model='fast-phi', messages=[
                {'role': 'system', 'content': system_rules},
                {'role': 'user', 'content': user_req}
            ])
            
            answer = response['message']['content']
            print(f"\n🚀 AI Suggestion:\n{answer}\n")
            print("-" * 30)
            
        except Exception as e:
            print(f"\n❌ Error: {e}")

if __name__ == "__main__":
    run_sh_assistant()
