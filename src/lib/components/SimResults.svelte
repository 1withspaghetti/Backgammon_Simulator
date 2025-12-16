<script lang="ts">
    import type { Results } from "$lib/assets/generated/simulation";


    let { results, time, winChance }: { results: Results, time: number, winChance: number } = $props();

    let sum = $derived(results.sum());
    const formatter = new Intl.NumberFormat(undefined, {
        notation: "compact",
        compactDisplay: "long",
    });

    let stats = $derived(results.probPerTurn())
</script>

<div class="flex flex-col items-center mt-2 w-full">
    <small class="mb-2 text-xs w-fit">Computed {formatter.format(sum)} outcome{sum === 1n ? '' : 's'} in {time >= 1 ? formatter.format(time) : '<1'} ms</small>
    <div>Average Turns To Win: <b title={stats.average+""}>{stats.average.toFixed(2)}</b></div>
    <div>Change of Winning: <b>{(winChance * 100).toFixed(2)}%</b></div>
    <table class="mt-4">
        <thead>
            <tr>
                <th class="px-2 border-r border-gray-600 text-right">Turn</th>
                <th class="px-2">% of Winning</th>
            </tr>
        </thead>
        <tbody>
            {#each stats.perTurn as chance, i}
                <tr class="border-t border-gray-600">
                    <td class="px-2 border-r border-gray-600 text-right">{i}</td>
                    <td class="px-2">{Math.round(chance * 100 * 1000)/1000}%</td>
                </tr>
            {/each}
        </tbody>
    </table>
</div>