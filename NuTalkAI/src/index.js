import React from 'react';
import ReactDOM from 'react-dom/client';
import { Game } from './Game.js';
import { UI } from './UI.js';
import './styles.css';

console.log('🔄 React App Rendered');

const MemoizedGame = React.memo(Game); // ✅ Prevent re-renders

const App = () => {
  return (
    <div className="app-container">
      <MemoizedGame />
      <UI />
    </div>
  );
};

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(<App />);
