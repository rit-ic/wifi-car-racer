import * as React from 'react';
import * as ReactDOM from 'react-dom/client';
import { MantineProvider, Button } from '@mantine/core';
import App from './App';

export default ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <MantineProvider withGlobalStyles withNormalizeCSS>
      <App />
    </MantineProvider>
  </React.StrictMode>
);