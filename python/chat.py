import ollama
import sys

def ask_ai():
    print("--- AI Terminal Assistant (Phi-3) ---")
    print("Type 'exit' to quit.\n")
    
    while True:
        user_input = input("You: ")
        if user_input.lower() in ['exit', 'quit']:
            break
            
        print("\nAI: ", end="")
        sys.stdout.flush()
        
        try:
            # Setting stream=True is the magic fix
            stream = ollama.chat(
                model='fast-phi',
                messages=[{'role': 'user', 'content': user_input}],
                stream=True,
            )
            
            for chunk in stream:
                content = chunk['message']['content']
                print(content, end="")
                sys.stdout.flush() # Forces each word to appear now
            print("\n") # New line after finished
            
        except Exception as e:
            print(f"\nError: {e}")

if __name__ == "__main__":
    ask_ai()
