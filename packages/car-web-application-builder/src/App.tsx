import * as React from "react";
import {
  Button,
  Container,
  Grid,
  Group,
  Paper,
  SegmentedControl,
  Stack,
  Text,
} from "@mantine/core";
import { Blink } from "./pages/Blink";
import { Normal } from "./pages/Normal";
import { getState, sendCommand } from "./api/ServerAPI";
import { State } from "./common/interfaces";

function App() {
  const [state, setState] = React.useState<State>({
    led1: true,
    led2: true,
    blinking: true,
    together: false,
    delay: 0,
  });

  const onSegmentChanged = (newValue: string) => {
    sendCommand([["blink", [newValue].includes("false") ? "OFF" : "ON"]]);
    getState(console.log);
    getState(setState);
  };

  React.useEffect(() => {
    console.log("USED EFFECT");
    getState(console.log);
    getState(setState);
  }, []);

  const updateMotor = async (
    id: number,
    state: "FORWARD" | "BACKWARD" | "STOP"
  ) => {
    console.log(`Sending ${state} to motor ${id}`);
    sendCommand([[`m${id}`, `${state}`]]);
  };

  return (
    <Container size="sm" my="lg">
      <Paper shadow="xs">
        <Grid grow>
          <Grid.Col span={4}></Grid.Col>
          <Grid.Col span={4}><Button onClick={()=>{
            updateMotor(1, "FORWARD");
            updateMotor(2, "FORWARD");
            updateMotor(3, "BACKWARD");
            updateMotor(4, "BACKWARD");
          }}>FORWARD</Button></Grid.Col>
          <Grid.Col span={4}></Grid.Col>
          <Grid.Col span={4}><Button onClick={()=>{
            updateMotor(1, "FORWARD");
            updateMotor(2, "FORWARD");
            updateMotor(3, "FORWARD");
            updateMotor(4, "FORWARD");
          }}>LEFT</Button></Grid.Col>
          <Grid.Col span={4}><Button onClick={()=>{
            updateMotor(1, "STOP");
            updateMotor(2, "STOP");
            updateMotor(3, "STOP");
            updateMotor(4, "STOP");
          }}>STOP</Button></Grid.Col>
          <Grid.Col span={4}><Button onClick={()=>{
            updateMotor(1, "BACKWARD");
            updateMotor(2, "BACKWARD");
            updateMotor(3, "BACKWARD");
            updateMotor(4, "BACKWARD");
          }}>RIGHT</Button></Grid.Col>
          <Grid.Col span={4}></Grid.Col>
          <Grid.Col span={4}><Button onClick={()=>{
            updateMotor(1, "BACKWARD");
            updateMotor(2, "BACKWARD");
            updateMotor(3, "FORWARD");
            updateMotor(4, "FORWARD");
          }}>FORWARD</Button></Grid.Col>
          <Grid.Col span={4}></Grid.Col>
        </Grid>
        <Stack spacing="xl" p="lg">
          <Stack>
            <Text>Motor 1</Text>
            <Group>
              <Button
                onMouseUp={() => updateMotor(1, "STOP")}
                onMouseDown={() => updateMotor(1, "FORWARD")}
              >
                FORWARD
              </Button>
              <Button
                onMouseUp={() => updateMotor(1, "STOP")}
                onMouseDown={() => updateMotor(1, "BACKWARD")}
              >
                BACKWARD
              </Button>
            </Group>
          </Stack>
          <Stack>
            <Text>Motor 2</Text>
            <Group>
              <Button
                onMouseUp={() => updateMotor(2, "STOP")}
                onMouseDown={() => updateMotor(2, "FORWARD")}
              >
                FORWARD
              </Button>
              <Button
                onMouseUp={() => updateMotor(2, "STOP")}
                onMouseDown={() => updateMotor(2, "BACKWARD")}
              >
                BACKWARD
              </Button>
            </Group>
          </Stack>
          <Stack>
            <Text>Motor 3</Text>
            <Group>
              <Button
                onMouseUp={() => updateMotor(3, "STOP")}
                onMouseDown={() => updateMotor(3, "FORWARD")}
              >
                FORWARD
              </Button>
              <Button
                onMouseUp={() => updateMotor(3, "STOP")}
                onMouseDown={() => updateMotor(3, "BACKWARD")}
              >
                BACKWARD
              </Button>
            </Group>
          </Stack>
          <Stack>
            <Text>Motor 4</Text>
            <Group>
              <Button
                onMouseUp={() => updateMotor(4, "STOP")}
                onMouseDown={() => updateMotor(4, "FORWARD")}
              >
                FORWARD
              </Button>
              <Button
                onMouseUp={() => updateMotor(4, "STOP")}
                onMouseDown={() => updateMotor(4, "BACKWARD")}
              >
                BACKWARD
              </Button>
            </Group>
          </Stack>
          {/* <Text weight={600}>Kontroliraj Lampice</Text>
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
          {state.blinking && <Blink state={state} setState={setState} />} */}
        </Stack>
      </Paper>
    </Container>
  );
}

export default App;
