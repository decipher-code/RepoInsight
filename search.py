import chromadb

# 1. Connect to the existing DB
client = chromadb.PersistentClient(path="./repo_db")
collection = client.get_collection(name="music_player_repo")

def search_code(query_text, n_results=3):
    print(f"Searching for: '{query_text}'...")
    results = collection.query(
        query_texts=[query_text],
        n_results=n_results
    )
    
    # Results are lists of lists (one list per query)
    for i in range(len(results['documents'][0])):
        doc = results['documents'][0][i]
        meta = results['metadatas'][0][i]
        dist = results['distances'][0][i]
        
        print(f"\n--- Result {i+1} (Distance: {dist:.4f}) ---")
        print(f"File: {meta['file']}")
        print(f"Type: {meta['type']}")
        print(f"Name: {meta['name']}")
        print(f"Code:\n{doc.strip()}\n")

if __name__ == "__main__":
    # Example query
    user_query = "how are users saved to file" 
    search_code(user_query)
