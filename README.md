# PowerMeter

## 1. 模块作用

CAN 功率计：解析 0x213 帧（D[0..1] 电压、D[2..3] 电流，小端 int16，单位 0.01 V / 0.01 A），并算出功率。

CAN power meter decoding voltage/current and computing power.

## 2. 构造接口

```cpp
PowerMeter(CanRouter& router, CanRouter::Bus bus, uint32_t host_id = 0,
           uint32_t motor_id = 0x213);
```

依赖参数 / Dependencies:

- `CanRouter& router`、`CanRouter::Bus bus`

配置参数 / Configuration:

- `host_id` — 只接收，填 0
- `motor_id` — 接收帧 ID，默认 `0x213`

## 3. 公开接口

- `voltage` / `current` / `power` / `rx_cnt`
- `static PowerMeter* Instance()`

## 4. 配置示例

```yaml
modules:
  - module: LinShen857/PowerMeter
    id: power_meter
    args:
      - router: can_router
      - bus: CanRouter::Bus::CAN1
      - host_id: '0'
      - motor_id: '0x213'
```

## 5. 依赖与硬件

模块依赖 / Module dependencies:

- `LinShen857/CanDevice`
- `LinShen857/CanRouter`

硬件 / Hardware:

- `LibXR::CAN`
