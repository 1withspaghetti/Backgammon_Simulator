<script lang="ts">

    let { board = $bindable<number[]>([0, 0, 0, 0, 0, 0]) } = $props();

    
</script>

<div class="w-fit h-min grid grid-cols-6 gap-x-2 bg-gray-50 p-2 rounded-lg shadow-md">
    {#each { length: 15 }, _y}
        {@const y = 15 - _y /* NOTE: Not zero-indexed however x is */}
        {#each { length: 6 }, x}
            <button 
                type="button" 
                aria-label="Game Piece" 
                onclick={() => board[x] = (board[x] == y ? y-1 : y)}
                class="w-8 h-8 rounded-full cursor-pointer {board[x] >= y ? 'bg-gray-700 hover:bg-gray-500 shadow' : 'bg-gray-100 hover:bg-gray-200 shadow-inner'} transition">
            </button>
        {/each}
    {/each}
    {#each { length: 6 }, x}
        <button 
            type="button" 
            aria-label="Game Piece" 
            onclick={() => board[x] = 0}
            class="w-8 h-8 cursor-pointer flex items-center justify-center text-2xl font-bold text-gray-300 hover:text-gray-400 transition">
            ×
        </button>
    {/each}
</div>