import { GoogleGenerativeAI } from '@google/generative-ai';
export class AI {
  constructor() {
    this.SYS_INSTRUC =
      'You are a baker named Jose. You only speak Spanish and you speak simply such that a very early beginner could understand. You only use once sentance at a time.';
    this.genAI = new GoogleGenerativeAI(
      'AIzaSyAllCh3_pH6r__TejSRM7o3X-6LrfnGOdo',
    );

    this.model = this.genAI.getGenerativeModel({
      model: 'gemini-2.0-flash',
      systemIntruction: this.SYS_INSTRUC,
    });

    this.chat = this.model.startChat();
  }

  async speech(input) {
    let result = await this.chat.sendMessage(input);
    return result.response.candidates[0].content.parts[0].text;
  }
}
