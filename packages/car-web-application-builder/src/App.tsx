import * as React from 'react';
import { Container, Paper, SegmentedControl, Stack, Text } from '@mantine/core';
import { Blink } from './pages/Blink';
import { Normal } from './pages/Normal';
import { getState, sendCommand } from './api/ServerAPI';
import { State } from './common/interfaces';

function App() {
  const [state, setState] = React.useState<State>({
    led1: true,
    led2: true,
    blinking: true,
    together: false,
    delay: 0
  });

  const onSegmentChanged = (newValue: string) => {
    sendCommand([["blink", [newValue].includes('false')?"OFF":"ON"]]);
    getState(console.log);
    getState(setState);
  }

  React.useEffect(()=>{
    console.log("USED EFFECT");
    getState(console.log);
    getState(setState);
  }, []);

  return (
    <Container size="sm" my="lg">
      <Paper shadow="xs">
        <Stack spacing="xl" p="lg">
          <Text weight={600}>Kontroliraj Lampice</Text>
          <SegmentedControl
            color="blue"
            value={state.blinking?"true":"false"}
            onChange={onSegmentChanged}
            data={[
              { label: 'Normalno', value: 'false' },
              { label: 'Treptanje', value: 'true' },
            ]}
          />
          {!state.blinking && <Normal state={state} setState={setState} />}
          {state.blinking && <Blink state={state} setState={setState} />}
        </Stack>
      </Paper>
    </Container>
  );
}

export default App;
