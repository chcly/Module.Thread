# Thread

Utility thread library.

## Testing

The Test directory is setup to work with [googletest](https://github.com/google/googletest).

## Building

![A1](https://github.com/chcly/Module.Thread/actions/workflows/build-linux.yml/badge.svg)
![A2](https://github.com/chcly/Module.Thread/actions/workflows/build-windows.yml/badge.svg)

```sh
mkdir build
cd build
cmake .. -DThread_BUILD_TEST=ON -DThread_AUTO_RUN_TEST=ON
make
```

### Optional defines

| Option                    | Description                                          | Default |
| :------------------------ | :--------------------------------------------------- | :-----: |
| Thread_BUILD_TEST         | Build the unit test program.                         |   ON    |
| Thread_AUTO_RUN_TEST      | Automatically run the test program.                  |   OFF   |
| Thread_USE_STATIC_RUNTIME | Build with the MultiThreaded(Debug) runtime library. |   ON    |
