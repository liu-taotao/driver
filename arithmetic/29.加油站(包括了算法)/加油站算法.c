
/**
 * @brief 这里的这个加油站算法, 也就是相当于总的油量减去消耗的是否不是负数
 *          还有就是每一次该加油站的油量减去消耗的不是负数, 那么位置就可以从这里开始
 * 
 * @param gas 
 * @param gasSize 
 * @param cost 
 * @param costSize 
 * @return int 
 */
int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize){
    // 总的剩余油量, 每一次是否有剩余的油量， 一次油量为正开始的位置
    int sumgas = 0, onegas = 0, res = 0;
    for (int i = 0; i < gasSize; i++) {
        sumgas += (gas[i] - cost[i]);
        onegas += (gas[i] - cost[i]);
        if (onegas < 0) {
            onegas = 0;
            res = i + 1;
        }
    }
    return sumgas > -1 ? res : -1;
}
