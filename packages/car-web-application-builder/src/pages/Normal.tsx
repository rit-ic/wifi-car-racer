import * as React from 'react';
import { State } from '../common/interfaces';
import { LedState } from '../components/LedState';

export const Normal = (props: {state: State, setState: Function}) => {

  return (
    <>
        <LedState name={"Bijele"} pin={0} mystate={props.state.led1||false} state={props.state} setState={props.setState} />
        <LedState name={"Šarene"} pin={1} mystate={props.state.led2||false} state={props.state} setState={props.setState} />
    </>
  );
}