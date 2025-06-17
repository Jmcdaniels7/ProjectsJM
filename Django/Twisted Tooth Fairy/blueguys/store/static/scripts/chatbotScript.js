window.addEventListener("DOMContentLoaded", function () {
    const sendBtn = document.getElementById("send-btn");
    const input = document.getElementById("chat-input");
    const chatArea = document.getElementById("chat-area");

    let waitingForOrderConfirmation = false;
    let awaitingReturnOrderId = false;
    let userData = [];


    const timeNow = new Date().toLocaleTimeString([], { hour: '2-digit', minute: '2-digit'});
    function botMessage(string){
      setTimeout(() => {
        const botBubble = document.createElement("div");
        botBubble.className = "recieved-chats recieved-msg recieved-msg-inbox";
        botBubble.innerHTML = `<p>${string}</p>
        <span class="time" id="msg-time">${new Date().toLocaleTimeString([], { hour: '2-digit', minute:"2-digit"})}</span>`;
        chatArea.appendChild(botBubble);
        chatArea.scrollTop = chatArea.scrollHeight;
      }, 600);
    };

    async function loadUserData(){
      try {
        const response = await fetch("/static/fakeData/data.json");
        if (!response.ok) {
          throw new Error('Unable to connect to DB: ' + response.statusText);
        }
        const data = await response.json();
        userData = data.data;
        return userData;
      } catch (error) {
        console.error('Error fetching user data', error);
        botMessage("Error loading user data");
        return [];
      }
    }

    botMessage("Hello, How can I help you?")
    //This is serving as a test function as well as an intro, it's to confirm Bot reply functions for later and timestamp handling. 
    //moved from the hard coded message on the HTML page.
    async function handleUserMsg() {
      const message = input.value.trim();
      if (message === "") return;
        //creates the div for reply and slaps it onto the HTML page
      const userBubble = document.createElement("div");
      userBubble.className = "user-message user-message";
      userBubble.innerHTML = `
      <p>${message}</p>
      <span class="time">${new Date().toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' })}</span>`;
      chatArea.appendChild(userBubble);
        //lowercase it to make it easier to parse
      const lowerMsg = message.toLowerCase();
        //reply to orders
        if (waitingForOrderConfirmation) {
            if (lowerMsg.includes("yes")) {
              await loadUserData();
              if (userData.length) {
                const user = userData[Math.floor(Math.random() * userData.length)];
                botMessage(`Looks like your order (order number: ${user.order}) was for ${user.description} at a total of $${user.price}.`);
              }
              waitingForOrderConfirmation = false;
              return;
            } else if (lowerMsg.includes("no")) {
              botMessage("Okay, returning you to the main menu.");
              waitingForOrderConfirmation = false;
              return;
            } else {
              botMessage("Please respond with 'Yes' or 'No'.");
              return;
            }
          }
        //Need to validate input to look for just orderID in there instead of the whole message.
        // so if someone sends in "order 12434" it just looks for the number, and ignores the order part.
        if (awaitingReturnOrderId) {
            const matchedOrder = userData.find(user => user.order === message);
            if (matchedOrder) {
              let reply = "";
              switch (matchedOrder.orderStatus.toLowerCase()) {
                case "delivered":
                    // !!! ADD PATH ONCE IT GETS PLACED INTO THE SYSTEM !!!
                  reply = `Got it! Let's start the return process. Click <a href="/static/fakeShippingLabel.png" target="_blank">here</a> to view your shipping label. Once we receive the item back, your account will be refunded.`;
                  break;
                case "in transit":
                  reply = `Your order is currently in transit. Please wait for it to arrive before starting a return.`;
                  break;
                case "ordered":
                  reply = `Your order has not been delivered yet, so it has been cancelled.`;
                  break;
                default:
                  reply = `Unknown error, please contact support.`;
              }
              botMessage(reply);
            } else {
              botMessage("That order ID wasn't found. Try again.");
            }
            awaitingReturnOrderId = false;
            return;
        }
      
          // Main command options
        if (lowerMsg.includes("order")) {
        botMessage("Would you like to see your order history?");
        waitingForOrderConfirmation = true;
        } else if (lowerMsg.includes("return")) {
        await loadUserData();
        botMessage("What is the order ID you would like to return?");
        awaitingReturnOrderId = true;
        } else if (lowerMsg.includes("help")) {
        botMessage("Type 'orders' or 'returns' to get started.");
        } else {
        botMessage("I don't understand. Try 'orders', 'returns', or 'help'.");
        }
    
        input.value = "";
        chatArea.scrollTop = chatArea.scrollHeight;
        }
      
        sendBtn.addEventListener("click", handleUserMsg);
        input.addEventListener("keydown", function (event) {
          if (event.key === "Enter") {
            event.preventDefault();
            handleUserMsg();
      }
    });
  });
