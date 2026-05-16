async function sendMessage() {
    const input = document.getElementById("user-input");
    const chatLog = document.getElementById("chat-log");

    let message = input.value.trim();
    
    if (!message) return;

    // Add user message
    chatLog.innerHTML += `<p><strong>You:</strong> ${escapeHtml(message)}</p>`;
    chatLog.scrollTop = chatLog.scrollHeight;

    const response = await fetch("/chat", {
        method: "POST",
        headers: {"Content-Type": "application/json"},
        body: JSON.stringify({message: message})
    });

    const data = await response.json();

    chatLog.innerHTML += `<p><strong>Bot:</strong> ${escapeHtml(data.response)}</p>`;
    chatLog.scrollTop = chatLog.scrollHeight;

    input.value = "";
}

function escapeHtml(text) {
    const div = document.createElement('div');
    div.textContent = text;
    return div.innerHTML; 
}
