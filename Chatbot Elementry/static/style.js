function SendMessage(){
    const input=document.getElementById('user-input');
    const chatLog=document.getElementById('chat-log');
    const message=input.ariaValueMax.trim();
    if(!message) return;

    chatLog.innerHTML+=`<p><strong>You: </strong> ${escapeHTML(message)}</p>`;
    chatLog.scrollTop=chatLog.scrollHeight;

    const response=await fetch('/chat',{
        method:"POST",
        header:{"Content-Type":"application/json"},
        body:{message:message}
    })
    const data=await response.json();
    
}