import Phaser from 'phaser';
import React, { useEffect, useRef } from 'react';
import { DialogueScene } from './scenes/DialogueScene.js';

export function Game() {
  const gameRef = useRef(null);

  console.log('🔄 Game Component Rendered');

  useEffect(() => {
    if (window.PHASER_GAME) {
      console.warn('Game already running, skipping creation');
    }
    if (!gameRef.current) {
      const config = {
        type: Phaser.AUTO,
        width: 800,
        height: 600,
        parent: 'game-container',
        scene: [DialogueScene],
      };
      gameRef.current = new Phaser.Game(config);
    }
    return () => {
      if (gameRef.current) {
        console.log('🛑 Destroying Phaser Game...');
        gameRef.current.destroy(true);
        gameRef.current = null;
      }
    };
  }, []);

  return <div id="game-container"></div>;
}
