
export const sendCommand = async (params: string[][]) => {
    await fetch(`./command?${new URLSearchParams(params)}`, {method: "GET"});
}

export const getState = (callback: Function) => {
    fetch(`./status`, {method: "GET"})
    .then(async (response)=>{
        callback(await response.json());
    })
    .catch((error)=> {
        console.log(error);
    });
}

const generateParams = (status: string) => {
    return new URLSearchParams([
        ['status', status]
    ]);
}

// <form action="./toggle" method="GET">
//         <select name="status" id="status">
//             <option default>Odaberi</option>
//             <option value="0">Upali sve</option>
//             <option value="1">Ugasi sve</option>
//             <option value="2">Upali bijele</option>
//             <option value="3">Ugasi bijele</option>
//             <option value="4">Upali šarene</option>
//             <option value="5">Ugasi šarene</option>
//             <option value="6">Naizmjence sporo</option>
//             <option value="7">Naizmjence brzo</option>
//         </select>
//         <input type="submit" value="Potvrdi">
//     </form>