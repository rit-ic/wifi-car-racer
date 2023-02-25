export const sendCommand = async (params: string[][]) => {
    await fetch(`./command?${new URLSearchParams(params)}`, {method: "GET"});
}

export const getStatus = (callback: Function) => {
    fetch(`./status`, {method: "GET"})
    .then(async (response)=>{
        callback(await response.json());
    })
    .catch((error)=> {
        console.log(error);
    });
}
