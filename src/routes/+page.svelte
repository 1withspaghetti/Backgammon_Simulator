<script lang="ts">
    import loadModule, { type MainModule, type Results, type ResultsProbability } from '$lib/assets/generated/simulation';
    import Board from '$lib/components/Board.svelte';
    import SimResults from '$lib/components/SimResults.svelte';
    import { setContext } from 'svelte';

    // Load the simulator wasm and provide it to the children
    let simulator: MainModule|undefined = $state(undefined);
    $effect(() => void loadModule().then(wasm => simulator = wasm));

    let board: number[] = $state(new Array(6).fill(0));
    let oppBoard: number[] = $state(new Array(6).fill(0));

    let results: Results|undefined = $state(undefined);
    let resultsTime = $state(0);
    let oppResults: Results|undefined = $state(undefined);
    let oppResultsTime = $state(0);
    let winChance: number|undefined = $state(undefined);

    $effect(() => {
        if (!simulator) return;
        let start = Date.now();
        let res = simulator.simulate(new simulator.Board(board[0], board[1], board[2], board[3], board[4], board[5]))
        results = res;
        resultsTime = Date.now() - start;
        return () => res.delete();
    })

    $effect(() => {
        if (!simulator) return;
        let start = Date.now();
        let res = simulator.simulate(new simulator.Board(oppBoard[0], oppBoard[1], oppBoard[2], oppBoard[3], oppBoard[4], oppBoard[5]))
        oppResults = res;
        oppResultsTime = Date.now() - start;
        return () => res.delete();
    })

    $effect(() => {
        if (!simulator) return;
        if (!results || !oppResults) return;
        winChance = simulator.chanceWin(results, oppResults);
    })

</script>

<main class="p-4 sm:p-8">
    <div class="flex gap-4 flex-wrap justify-center">
        <div>
            <h2 class="text-center text-2xl mb-2">My Board</h2>
            <Board bind:board={board} />
            {#if results}<SimResults results={results} time={resultsTime} winChance={winChance || 0} />{/if}
        </div>
        <div>
            <h2 class="text-center text-2xl mb-2">Opponent's Board</h2>
            <Board bind:board={oppBoard} />
            {#if oppResults}<SimResults results={oppResults} time={oppResultsTime} winChance={1-(winChance ?? 1)} />{/if}
        </div>
    </div>
</main>
