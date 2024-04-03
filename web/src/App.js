import Selector from "./Selector/Selector"
import ScenarioCollapse from "./ScenarioCollapse/ScenarioCollapse"
function App() {
  return (
    <div style={{display: 'flex', justifyContent: 'center', flexDirection: 'column', alignItems: 'center'}}>
        <h1>
            Scheduling for Smart Grid (Demo Site)
        </h1>
        <h2>
            Choose some scenarios to compare
        </h2>
        <Selector/>
        <h2>
            Check all of scenarios below
        </h2>
        <ScenarioCollapse/>
    </div>
  );
}

export default App;
