## prepare


```bash
mkdir build && cd build
```

## compile

```bash
cmake .. && make -j8
```

## options

If you have giroscope on your laptop, you can enable one feature.

```bash
cmake .. -DGIRO=on && make -j8
```

## launch

```
./gui
```
