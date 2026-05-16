from flask import Flask,render_template,request,jsonify
import re

app=Flask(__name__)

def chatbot_response(message):
    msg=message.lower()
    if re.search(r"\b(hello|hi|hey)\b", msg):
        return "Hello! Welcome to TechGear Store."
    elif "price" in msg or "pricing" in msg:
        return "Headphones ₹2000, Smartwatch ₹3500, Keyboard ₹2500, Mouse ₹1200."
    elif "time" in msg or "hours" in msg or "timing" in msg:
        return "Our store is open from 9 AM to 8 PM."
    elif "contact" in msg or "number" in msg or "no." in msg:
        return "You can contact us at +91-9999999999."
    elif re.search(r"\b(product|thing|item|sell)\b", msg):
        return "We sell Headphones, Smartwatch, Keyboard, and Gaming Mouse."
    else:
        return "Sorry, I didn't understand. Please ask about products, price, or contact."
    
@app.route("/")
def home():
    return render_template("index.html")

@app.route("/chat", methods=["POST"])
def chat():
    user_message = request.json["message"]
    response = chatbot_response(user_message)
    return jsonify({"response": response})

if __name__ == "__main__":
    app.run(debug=True)



# This code transitions your practical application into **Natural Language Processing (NLP)** and **Rule-Based Expert Systems**, which is covered under *Unit 4: NLP & Chatbots / Rule-Based Systems* in the SPPU Artificial Intelligence curriculum.

# Here are 15 highly targeted oral (viva) questions tailored to this Flask-based chatbot application.

# ---

# ## 💡 Category 1: AI & Chatbot Architecture Theory

# ### 1. What type of chatbot architecture does this code implement? What are its limitations?

# * **Answer:** This is a **Rule-Based (or Scripted) Chatbot**. It relies entirely on hardcoded keywords and regular expressions (`re.search`) to match user input with predefined responses.
# * **Limitations:** It lacks any understanding of context, intent, synonyms, or semantic meaning. If a user makes a typo or phrases a question uniquely (e.g., "What's the damage to my wallet for a mouse?"), the chatbot will default to the "Sorry, I didn't understand" fallback message.



# ### 2. How does a rule-based chatbot differ fundamentally from a generative AI chatbot (like ChatGPT)?

# * **Answer:**
# * **Rule-Based Chatbots** are deterministic. They map specific inputs directly to fixed responses based on explicit syntax rules. They cannot generate brand-new strings of text.
# * **Generative Chatbots** utilize Large Language Models (LLMs) and neural networks to analyze the probability of the next best token. They dynamically synthesize unique responses based on patterns learned during training.



# ### 3. In the context of AI, what are "Intents" and "Entities"? How are they represented in your code?

# * **Answer:**
# * **Intent:** The user's underlying goal or purpose behind a message (e.g., inquiring about prices). In your code, intents are mapped via `if` conditions like `"price" in msg`.
# * **Entity:** The specific data point or object the user references (e.g., "Headphones"). In this basic script, entities are not isolated or extracted programmatically; they are simply hardcoded into static response sentences.



# ### 4. What is the role of the Regular Expression library (`re`) in this script from an AI perspective?

# * **Answer:** The `re` module acts as a basic **Pattern Matching Engine**. By using bounds like `r"\b(hello|hi|hey)\b"`, it verifies whether specific keyword variations exist as isolated, standalone words. This represents the simplest form of shallow textual lexical analysis.

# ---

# ## ⏱️ Category 2: Text Preprocessing & NLP Pipeline

# ### 5. Why do you execute `message.lower()` before evaluating any conditions?

# * **Answer:** Case folding/normalization is a fundamental text preprocessing step in NLP. It standardizes the input string by eliminating case variations ("Price", "PRICE", "pRiCe"), ensuring that subsequent string checks or regex rules don't miss matches due to capitalization.

# ### 6. If a user types "I want to buy a smart watch", will your current chatbot identify it? Why?

# * **Answer:** No, it will fail to match the product check. The code looks for the contiguous substring `"smartwatch"` inside the incoming text block. Spacing the term out as `"smart watch"` breaks the string verification, triggering the default `else` condition.

# ### 7. What basic NLP preprocessing steps are completely missing from this implementation?

# * **Answer:**
# * **Tokenization:** Breaking down sentences into individual words or tokens.
# * **Stemming/Lemmatization:** Reducing words to their root or base form (e.g., transforming "selling" or "sold" to "sell").
# * **Stop-word Removal:** Filtering out filler words ("and", "the", "is") that do not alter the core intent.



# ### 8. What is the overall Time and Space Complexity of a single conversation turn in your `chatbot_response` function?

# * **Answer:**
# * **Time Complexity:** $O(N \times K)$, where $N$ represents the character length of the user's message and $K$ represents the total number of keyword/regex checking rules. The string operations and regex functions must evaluate the input character-by-character.
# * **Space Complexity:** $O(N)$ to allocate and store the normalized lowercase version of the string (`msg`).



# ---

# ## 💻 Category 3: System Design & Integration (Flask)

# ### 9. Why is Flask an effective tool for deploying an AI agent or Chatbot model?

# * **Answer:** Flask is a lightweight WSGI web framework. It provides a simple architecture to expose python code (like an AI model or a response function) as an API endpoint over HTTP. This lets client applications (web fronts, mobile apps) seamlessly communicate with backend AI logic.

# ### 10. Explain how the `/chat` route operates. What data exchange format is utilized?

# * **Answer:** The `/chat` route accepts incoming HTTP `POST` requests. It extracts the raw text submitted by the user from a incoming JSON payload (`request.json["message"]`), feeds it directly to the `chatbot_response` processor, and encapsulates the return string into an outgoing JSON response package via `jsonify()`.

# ### 11. Your main block includes `app.run(debug=True)`. What does this do? Why is it risky for production deployments?

# * **Answer:** `debug=True` boots up an interactive debugger and enables auto-reloading whenever a source file changes. While ideal for development, it poses a severe security risk in production because it can expose interactive tracebacks and underlying source code directly to the browser end-user if an application error occurs.

# ---

# ## 🎯 Category 4: AI Variations & Scalability Questions

# ### 12. If your product line scales from 4 items to 10,000 items, why does this code architecture fail? How would you fix it?

# * **Answer:** Maintaining 10,000 hardcoded `elif` conditions is completely impossible and would degrade performance to $O(\text{Rules})$. To fix this, you decouple the data from the logic: store the items, prices, and hours in a database (SQL or NoSQL). When an intent is matched, query the database dynamically to generate the output string.

# ### 13. How could you upgrade this system to utilize an "Informed" NLP approach without jumping to full LLMs?

# * **Answer:** You can integrate Python NLP libraries like **NLTK** or **SpaCy**. Instead of checking basic substrings, you can compute text similarities, use a TF-IDF vectorizer, or train a lightweight Intent Classification model (like a Naive Bayes classifier) using tools like **Scikit-Learn** or **Rasa**.

# ### 14. What would happen if a user enters an empty string or symbols like "???" into the chat window?

# * **Answer:** The input bypasses all explicit conditional loops because it lacks any target keywords or alphanumeric regex matches. It safely drops into the final catch-all `else` fallback block, returning: *"Sorry, I didn't understand. Please ask about products, price, or contact."*

# ### 15. How would you introduce a conversational memory feature to this chatbot architecture?

# * **Answer:** Right now, the system is **stateless**—every request is treated as a standalone message. To track context, you can integrate Flask's native browser `session` object or back the service with a Redis caching layer to persist a unique user ID along with their past message history (e.g., tracking that the user previously selected "Headphones" when they follow up with "How much is it?").