/** @hidden */
const binding = require('../binding/macos-system-info');

export interface IKeyInfo {
    type: string;
    size: number;
}

export class SystemInfo {
    private system: any;

    constructor() {
        this.system = new binding.SystemInfo();
    }

    /**
     * Opens a new connection to the SMC.
     */
    public open() {
        this.system.open();
    }

    /**
     * Closes the connection to the SMC.
     */
    public close() {
        this.system.close();
    }

    /**
     * Returns information about the given SMC key. If the given key does not exist an exception is thrown.
     * @param key   The SMC key
     */
    public getKeyInfo(key: string): IKeyInfo {
        return this.system.getKeyInfo(key);
    }

    /**
     * Returns the current ram usage in gigabyte.
     * The function returns an array with 5 values:
     * [free, active, inactive, wired, compressed]
     */
    public getMemoryUsage(): number[] {
        return this.system.getMemoryUsage();
    }

    /**
     * Returns the total amount of ram in gigabyte.
     */
    public getTotalMemory(): number {
        return this.system.getTotalMemory();
    }

    /**
     * Returns the current temperature of the cpu in degrees celcius.
     */
    public getCpuTemp(): number {
        return this.system.getCpuTemp();
    }

    /**
     * Returns the current cpu usage in percent of the user, system, idle and nice in an array with this order.
     */
    public getCpuUsage(): number[] {
        return this.system.getCpuUsage();
    }

    /**
     * Returns the number of fans of the machine.
     */
    public getFanCount(): number {
        return this.system.getFanCount();
    }

    /**
     * Returns the minimum rpm of the fan.
     * @param fanId The fan id
     */
    public getMinFanSpeed(fanId: number): number {
        return this.system.getMinFanSpeed(fanId);
    }

    /**
     * Returns the maximum rpm of the fan.
     * @param fanId The fan id
     */
    public getMaxFanSpeed(fanId: number): number {
        return this.system.getMaxFanSpeed(fanId);
    }

    /**
     * Returns the current rpm of the fan.
     * @param fanId The fan id
     */
    public getCurrentFanSpeed(fanId: number): number {
        return this.system.getCurrentFanSpeed(fanId);
    }

    /**
     * Returns the number of batteries.
     */
    public getBatteryCount(): number {
        return this.system.getBatteryCount();
    }

    /**
     * Returns true if the machine is on AC and returns false otherwise.
     */
    public isOnAc(): boolean {
        return this.system.isOnAc();
    }

    /**
     * Returns the health of the battery in percent.
     */
    public getBatteryHealth(): number {
        return this.system.getBatteryHealth();
    }

    /**
     * Returns the cycles of the battery.
     */
    public getBatteryCycles(): number {
        return this.system.getBatteryCycles();
    }
}
