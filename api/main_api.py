from fastapi import FastAPI
from pydantic import BaseModel
from agent import app as agent_app 

api = FastAPI(title="RepoInsight API")

class QueryRequest(BaseModel):
    query: str

@api.post("/analyze")
async def analyze_code(request: QueryRequest):
    
    inputs = {"messages": [("human", request.query)]}
    
    
    result = agent_app.invoke(inputs, config={"recursion_limit": 25})
    
    
    return {"response": result["messages"][-1].content}

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(api, host="0.0.0.0", port=8001)
