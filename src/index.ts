/** @hidden */
const binding = require('../binding/smc-node-kit.node');

export interface IKeyInfo {
    type: string;
    size: number;
}

export class SMCNodeKit {
    private smcKit: any;

    constructor() {
        this.smcKit = new binding.SMCNodeKit();
    }

    /**
     * Opens a new connection to the SMC.
     */
    public open() {
        this.smcKit.open();
    }

    /**
     * Closes the connection to the SMC.
     */
    public close() {
        this.smcKit.close();
    }

    /**
     * Returns information about the given SMC key. If the given key does not exist an exception is thrown.
     * @param key   The SMC key
     */
    public getKeyInfo(key: string): IKeyInfo {
        return this.smcKit.getKeyInfo(key);
    }

    /**
     * Returns the current temperature of the cpu in degrees celcius.
     */
    public getCpuTemp(): number {
        return this.smcKit.getCpuTemp();
    }

    /**
     * Returns the current cpu usage in percent of the user, system, idle and nice in an array with this order.
     */
    public getCpuUsage(): number[] {
        return this.smcKit.getCpuUsage();
    }

    /**
     * Returns the number of fans of the machine.
     */
    public getFanCount(): number {
        return this.smcKit.getFanCount();
    }

    /**
     * Returns the minimum rpm of the fan.
     * @param fanId The fan id
     */
    public getMinFanSpeed(fanId: number): number {
        return this.smcKit.getMinFanSpeed(fanId);
    }

    /**
     * Returns the maximum rpm of the fan.
     * @param fanId The fan id
     */
    public getMaxFanSpeed(fanId: number): number {
        return this.smcKit.getMaxFanSpeed(fanId);
    }

    /**
     * Returns the current rpm of the fan.
     * @param fanId The fan id
     */
    public getCurrentFanSpeed(fanId: number): number {
        return this.smcKit.getCurrentFanSpeed(fanId);
    }

    /**
     * Returns the number of batteries.
     */
    public getBatteryCount(): number {
        return this.smcKit.getBatteryCount();
    }

    /**
     * Returns true if the machine is on AC and returns false otherwise.
     */
    public isOnAc(): boolean {
        return this.smcKit.isOnAc();
    }

    /**
     * Returns the health of the battery in percent.
     */
    public getBatteryHealth(): number {
        return this.smcKit.getBatteryHealth();
    }

    /**
     * Returns the cycles of the battery.
     */
    public getBatteryCycles(): number {
        return this.smcKit.getBatteryCycles();
    }
}
