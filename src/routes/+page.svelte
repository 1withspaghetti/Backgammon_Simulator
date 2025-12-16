<script lang="ts">
    import loadModule, { type MainModule } from '$lib/assets/generated/simulation';
  import Board from '$lib/components/Board.svelte';
    import { setContext } from 'svelte';

    // Load the simulator wasm and provide it to the children
    let simulator: MainModule|undefined = $state(undefined);
    $effect(() => void loadModule().then(wasm => simulator = wasm));
    setContext("simulator", () => simulator);
</script>

<Board />
