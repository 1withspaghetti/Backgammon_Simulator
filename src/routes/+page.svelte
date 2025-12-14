<script lang="ts">
    import simulation from '$lib/assets/generated/simulation';
    
    const instance = simulation().then(wasm => {

        const board = new wasm.Board(0, 0, 0, 0, 0, 15); // Will be deleted by the simulate function
        
        const results = wasm.simulate(board); // Need to delete results ourselves;
        
        const prob = results.probPerTurn();
        console.log(prob);
        results.delete();
    })
</script>

<h1>Welcome to SvelteKit</h1>
<p>Visit <a href="https://svelte.dev/docs/kit">svelte.dev/docs/kit</a> to read the documentation</p>
