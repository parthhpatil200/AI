from flask import Flask, render_template, request
import heapq

app = Flask(__name__)

# ------------------ KNOWLEDGE BASE ------------------
knowledge_base = [
    {"symptoms": ["fever", "cough"], "disease": "Flu (Influenza)"},
    {"symptoms": ["cough", "shortness of breath", "fever"], "disease": "Pneumonia"},
    {"symptoms": ["cough", "shortness of breath"], "disease": "Asthma or Bronchitis"},
    {"symptoms": ["sore throat", "fever", "fatigue"], "disease": "Strep Throat"},
    {"symptoms": ["runny nose", "sneezing", "sore throat"], "disease": "Common Cold"},
    {"symptoms": ["cough", "night sweats", "weight loss"], "disease": "Tuberculosis (TB)"},

    {"symptoms": ["headache", "nausea"], "disease": "Migraine"},
    {"symptoms": ["headache", "fever", "stiff neck"], "disease": "Meningitis"},
    {"symptoms": ["dizziness", "nausea", "headache"], "disease": "Vertigo"},
    {"symptoms": ["headache", "blurred vision", "fatigue"], "disease": "Hypertension"},

    {"symptoms": ["chest pain"], "disease": "Possible Heart Problem"},
    {"symptoms": ["chest pain", "shortness of breath"], "disease": "Possible Heart Attack — Seek Emergency Care"},
    {"symptoms": ["chest pain", "shortness of breath", "fatigue"], "disease": "Angina"},
    {"symptoms": ["swollen legs", "shortness of breath"], "disease": "Heart Failure"},

    {"symptoms": ["fever", "rash"], "disease": "Measles"},
    {"symptoms": ["fever", "joint pain", "rash"], "disease": "Dengue Fever"},
    {"symptoms": ["fever", "fatigue", "loss of appetite"], "disease": "Typhoid"},
    {"symptoms": ["fever", "chills", "sweating"], "disease": "Malaria"},
    {"symptoms": ["fever", "vomiting", "diarrhea"], "disease": "Gastroenteritis"},

    {"symptoms": ["nausea", "vomiting", "diarrhea"], "disease": "Food Poisoning"},
    {"symptoms": ["abdominal pain", "bloating", "diarrhea"], "disease": "IBS"},
    {"symptoms": ["abdominal pain", "fever", "nausea"], "disease": "Appendicitis"},
    {"symptoms": ["nausea", "jaundice", "fatigue"], "disease": "Hepatitis"},
    {"symptoms": ["heartburn", "nausea", "bloating"], "disease": "Acid Reflux"},

    {"symptoms": ["joint pain", "fatigue"], "disease": "Rheumatoid Arthritis"},
    {"symptoms": ["joint pain", "swelling", "stiffness"], "disease": "Osteoarthritis"},
    {"symptoms": ["back pain", "fatigue"], "disease": "Back Strain"},
    {"symptoms": ["muscle pain", "fatigue", "headache"], "disease": "Fibromyalgia"},

    {"symptoms": ["rash", "itching"], "disease": "Allergy"},
    {"symptoms": ["rash", "blisters", "fever"], "disease": "Chickenpox"},
    {"symptoms": ["rash", "joint pain", "fatigue"], "disease": "Lupus"},

    {"symptoms": ["fatigue", "weight gain", "cold intolerance"], "disease": "Hypothyroidism"},
    {"symptoms": ["fatigue", "excessive thirst", "frequent urination"], "disease": "Diabetes"},
    {"symptoms": ["fatigue", "pale skin", "dizziness"], "disease": "Anaemia"},
    {"symptoms": ["frequent urination", "burning sensation"], "disease": "UTI"},
]

# ------------------ TREE NODE ------------------
class Node:
    def __init__(self):
        self.children = {}
        self.diseases = []

# ------------------ BUILD TREE ------------------
def build_tree():
    root = Node()
    for entry in knowledge_base:
        current = root
        for symptom in entry["symptoms"]:
            if symptom not in current.children:
                current.children[symptom] = Node()
            current = current.children[symptom]
        current.diseases.append(entry["disease"])
    return root

root = build_tree()

# ------------------ DFS SEARCH ------------------
def dfs_search(node, symptoms, index=0):
    if index == len(symptoms):
        return node.diseases if node.diseases else None

    symptom = symptoms[index]

    if symptom in node.children:
        return dfs_search(node.children[symptom], symptoms, index + 1)

    return None

# ------------------ A* SEARCH ------------------
def a_star_diagnose(input_symptoms):
    pq = []

    for entry in knowledge_base:
        disease_symptoms = entry["symptoms"]

        matched = len(set(input_symptoms) & set(disease_symptoms))
        total = len(disease_symptoms)

        h = total - matched   # heuristic
        f = h

        heapq.heappush(pq, (f, entry["disease"]))

    return heapq.heappop(pq)[1]

# ------------------ DIAGNOSE ------------------
def diagnose(symptoms):
    symptoms = [s.strip() for s in symptoms]

    # Try exact match (DFS)
    result = dfs_search(root, symptoms)

    if result:
        return "Exact Match: " + ", ".join(result)

    # Otherwise use A*
    return "Approximate Match: " + a_star_diagnose(symptoms)

# ------------------ ROUTES ------------------
@app.route("/")
def home():
    return render_template("index.html")

@app.route("/diagnose", methods=["POST"])
def diagnose_route():
    symptoms = request.form.get("symptoms", "").lower().split(",")
    result = diagnose(symptoms)
    return render_template("index.html", diagnosis=result)

# ------------------ RUN ------------------
if __name__ == "__main__":
    app.run(debug=True)