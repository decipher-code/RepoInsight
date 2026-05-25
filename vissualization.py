import networkx as nx
import matplotlib.pyplot as plt

# Load your graph
G = nx.read_gml("repo_graph.gml")

# Create a professional layout
plt.figure(figsize=(12, 8))
pos = nx.spring_layout(G, k=0.5, iterations=50)

# Draw nodes and edges
nx.draw_networkx_nodes(G, pos, node_size=700, node_color='#0078d4', alpha=0.8) # Microsoft Blue
nx.draw_networkx_edges(G, pos, width=1.0, alpha=0.5, edge_color='gray')
nx.draw_networkx_labels(G, pos, font_size=8, font_family='sans-serif')

plt.title("RepoInsight: C++ Dependency Knowledge Graph (51 Nodes)")
plt.axis('off')

# Save the image for your assets folder
plt.savefig("assets/dependency_graph.png", dpi=300, bbox_inches='tight')
print("Graph visualization saved to assets/dependency_graph.png")