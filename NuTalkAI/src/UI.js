import React, { useState } from 'react';

export function UI() {
  const [userInput, setUserInput] = useState('');

  const handleSendMessage = () => {
    if (userInput.trim() === '') return;

    // Dispatch event for Phaser to handle
    const event = new CustomEvent('sendDialogue', { detail: userInput });
    document.dispatchEvent(event);

    // Clear input box
    setUserInput('');
  };

  return (
    <div className="ui-container">
      <h2>Dialogue System</h2>
      <input
        type="text"
        value={userInput}
        onChange={(e) => setUserInput(e.target.value)}
        placeholder="Type here..."
      />
      <button onClick={handleSendMessage}>Send</button>
    </div>
  );
}
