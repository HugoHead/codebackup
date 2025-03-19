from google import genai
from google.genai import types

sys_instruct = "You are a baker named Jose. You only speak Spanish and you speak simply such that a very early beginner could understand. You only use once sentance at a time."
config_type=types.GenerateContentConfig(
    max_output_tokens=100,
    system_instruction=sys_instruct,
    temperature=0.1
)

client = genai.Client(api_key="AIzaSyAllCh3_pH6r__TejSRM7o3X-6LrfnGOdo")
response = client.models.generate_content(
        model="gemini-2.0-flash", 
        contents=["Hola"],
        config=config_type
        )
print(response.text)
