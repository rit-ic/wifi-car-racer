import * as React from 'react';
import { Card, Text, Badge, Button, Group } from '@mantine/core';
import { getState, sendCommand } from '../api/ServerAPI';
import { State } from '../common/interfaces';

export const LedState = (props: { name: string, pin: number, mystate: boolean, state: State, setState: Function }) => {

  const updateLed = async () => {
    sendCommand([['pin', `${props.pin}`], ['value', !props.mystate?"OFF":"ON"]]);
    getState(console.log);
    getState(props.setState);
  }

  return (
    <>
      <Group position="apart">
        <Text size={"sm"} weight={500}>{props.name} lampice</Text>
        <Badge color={!props.mystate ? "green" : "red"} variant="light">
          <p>{!props.mystate ? "Upaljene" : "Ugašene"}</p>
        </Badge>
      </Group>

      <Button variant="light" color="blue" fullWidth onClick={updateLed} radius="md">
         <p>{props.mystate ? "Upali" : "Ugasi"}</p>
      </Button>
    </>
  );
}