import * as React from "react";
import { Center, Container, Paper } from "@mantine/core";
import { sendCommand } from "./api/ServerAPI";
import { Joystick } from "react-joystick-component";
import { IJoystickUpdateEvent } from "react-joystick-component/build/lib/Joystick";

const updateMotor = async (
  id: number,
  state: "FORWARD" | "BACKWARD" | "STOP",
  speed: number
) => {
  // console.log(`Sending ${state} to motor ${id}, speed: ${speed}`);
  sendCommand([
    [`m${id}`, `${state}`],
    ["speed", `${speed}`],
  ]);
};

function App() {
  const onMove = (event: IJoystickUpdateEvent) => {
    const { type, x, y, distance, direction } = event;
    if (!distance) return;
    //(50-255)
    const d = distance - 40;
    const min = 50;
    const max = 255;
    let s = min + Math.floor(((max - min) / 40) * d);
    s = s < min ? min : s > max ? max : s;
    switch (direction) {
      case "RIGHT":
        updateMotor(1, "FORWARD", s);
        updateMotor(2, "BACKWARD", s);
        updateMotor(3, "FORWARD", s);
        updateMotor(4, "BACKWARD", s);
        break;
      case "LEFT":
        updateMotor(1, "BACKWARD", s);
        updateMotor(2, "FORWARD", s);
        updateMotor(3, "BACKWARD", s);
        updateMotor(4, "FORWARD", s);
        break;
      case "FORWARD":
        updateMotor(1, "FORWARD", s);
        updateMotor(2, "FORWARD", s);
        updateMotor(3, "FORWARD", s);
        updateMotor(4, "FORWARD", s);
        break;
      case "BACKWARD":
        updateMotor(1, "BACKWARD", s);
        updateMotor(2, "BACKWARD", s);
        updateMotor(3, "BACKWARD", s);
        updateMotor(4, "BACKWARD", s);
        break;
    }
  };

  const onStop = () => {
    updateMotor(1, "STOP", 0);
    updateMotor(2, "STOP", 0);
    updateMotor(3, "STOP", 0);
    updateMotor(4, "STOP", 0);
  };

  return (
    <Container size="sm" my="lg">
      <Paper shadow="xs">
        <Center style={{ minHeight: "60vh" }}>
          <Joystick
            size={200}
            stickSize={100}
            throttle={100}
            baseColor={"#0099ff55"}
            stickColor={"#0099ff"}
            minDistance={30}
            move={onMove}
            stop={onStop}
            sticky={false}
          />
        </Center>
      </Paper>
    </Container>
  );
}

export default App;
