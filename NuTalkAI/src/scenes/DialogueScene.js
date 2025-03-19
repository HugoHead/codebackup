import Phaser from 'phaser';
import { AI } from '../api/geminiAPI.js';

export class DialogueScene extends Phaser.Scene {
  constructor() {
    super({ key: 'DialogueScene' });
    this.dialogueAI = new AI(); // AI class for NPC responses
    if (this.sceneInitialized) {
      console.warn('⚠️ DialogueScene Already Initialized, Skipping...');
      return;
    }
    this.sceneInitialized = true; // ✅ Prevent duplicate initialization
    console.log('✅ DialogueScene Constructor Called');
  }

  preload() {
    this.load.image('Jose', 'Jose.webp'); // Load NPC image
    this.load.image('PC', 'PC.webp'); // Load player image
  }

  create() {
    if (this.sceneStarted) {
      console.warn('⚠️ Scene was already initialized. Skipping.');
      return;
    }
    console.log('Creating NPC and Player Sprites...');
    // **Display NPC and Player Images**
    this.playerSprite = this.add.image(150, 300, 'PC').setScale(0.25);
    this.npcSprite = this.add.image(650, 300, 'Jose').setScale(0.25);

    // **Check if Phaser is adding duplicate text elements**
    if (this.dialogueBox) {
      console.warn('Duplicate Dialogue Box Detected!');
    }

    // **Dialogue Box**
    this.dialogueBox = this.add.text(250, 500, 'Type below to talk', {
      fontSize: '20px',
      fill: '#fff',
      backgroundColor: '#000',
      padding: { x: 10, y: 5 },
    });

    // **Response Box**
    this.responseText = this.add.text(250, 550, '', {
      fontSize: '18px',
      fill: '#fff',
      backgroundColor: '#222',
      padding: { x: 10, y: 5 },
    });

    // **Listen for Dialogue Input from React UI**
    document.addEventListener('sendDialogue', async (event) => {
      const userInput = event.detail;
      this.dialogueBox.setText('You: ' + userInput);

      // **Get AI Response**
      const aiResponse = await this.dialogueAI.speech(userInput);
      this.responseText.setText('Jose: ' + aiResponse);
    });
  }
}
