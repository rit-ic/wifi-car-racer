import * as React from 'react';
import { Slider, Text, Radio, Group, Container } from '@mantine/core';
import { getState, sendCommand } from '../api/ServerAPI';
import { State } from '../common/interfaces';

export const Blink = (props: { state: State, setState: Function }) => {

  const [value, setValue] = React.useState(1000);

  const onEndValue = async (value: number) => {
    sendCommand([["delay", `${value}`]])
    getState(console.log);
    getState(props.setState);
  }
  const onModeChange = async (value: string) => {
    sendCommand([["together", `${value}`]])
    getState(console.log);
    getState(props.setState);
  }

  return (
    <>
      <Group position="apart">
        <Text size={"sm"} weight={500}>Odaberi način</Text>
        <Radio.Group
          value={props.state.together?"true":"false"}
          onChange={onModeChange}
        >
          <Radio value="false" label="Naizmjence" />
          <Radio value="true" label="Zajedno" />
        </Radio.Group>

      </Group>

      <Text size={"sm"} weight={500}>Odaberi brzinu ({props.state.delay} milisekundi)</Text>
      <Slider value={value} min={10} max={2000} step={10} onChange={setValue} onChangeEnd={onEndValue} />

    </>
  );
}