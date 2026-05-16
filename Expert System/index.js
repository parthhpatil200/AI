function sendMsg(){
    let input = document.getElementById("userIp").value.toLowerCase();
    let displayIp = document.getElementById("userIp").value
let chatbox = document.getElementById("chatbox")

chatbox.innerHTML += "<p class='user'><b>You:</b> "+displayIp+"</p>"
let response="";
// Greeting
            if(input.includes("hello") ||
               input.includes("hi") ||
               input.includes("hey")){

                response =
                "Hello! How can I help you today?";
            }

            // Courses
            else if(input.includes("course")){

                response =
                "We offer Web Development, AI, Machine Learning, Data Science, Cloud Computing and Cyber Security courses.";
            }

            // Fees
            else if(input.includes("fees") ||
                    input.includes("price") ||
                    input.includes("cost")){

                response =
                "Course prices start from Rs.999 depending on the course.";
            }

            // Certificates
            else if(input.includes("certificate")){

                response =
                "Yes, certificates are provided after successful course completion.";
            }

            // Duration
            else if(input.includes("duration")){

                response =
                "Most courses range from 4 weeks to 6 months.";
            }

            // Placement
            else if(input.includes("placement")){

                response =
                "Yes, placement assistance and interview preparation are available.";
            }

            // Python
            else if(input.includes("python")){

                response =
                "We provide Python Basics, Python Full Stack and Python for AI courses.";
            }

            // AI
            else if(input.includes("ai") ||
                    input.includes("machine learning")){

                response =
                "Our AI courses include Machine Learning, Deep Learning and Generative AI.";
            }

            // Web Development
            else if(input.includes("web development")){

                response =
                "We teach HTML, CSS, JavaScript, React and Node.js in Web Development.";
            }

            // Instructor
            else if(input.includes("instructor") ||
                    input.includes("teacher")){

                response =
                "Instructors can upload and sell their own courses on LearnHub.";
            }

            // Login
            else if(input.includes("login")){

                response =
                "You can login using your email and password.";
            }

            // Signup
            else if(input.includes("signup") ||
                    input.includes("register")){

                response =
                "You can register as a student or instructor on our platform.";
            }

            // Payment
            else if(input.includes("payment")){

                response =
                "We support UPI, Debit Card, Credit Card and Net Banking.";
            }

            // Refund
            else if(input.includes("refund")){

                response =
                "Refunds are available within 7 days of purchase.";
            }

            // Support
            else if(input.includes("support") ||
                    input.includes("help")){

                response =
                "Our support team is available 24x7.";
            }

            // Contact
            else if(input.includes("contact")){

                response =
                "Contact us at support@learnhub.com";
            }

            // Thank You
            else if(input.includes("thank")){

                response =
                "You're welcome! Happy Learning.";
            }

            // Bye
            else if(input.includes("bye")){

                response =
                "Goodbye! Have a great day.";
            }

            // Default Response
            else{

                response =
                "Sorry, I could not understand your question.";
            }

chatbox.innerHTML += "<p class='bot'><b>Bot:</b> " + response +"</p>"
document.getElementById("userIp").value = "";
}

