# CBuffer


My circular buffer implementation

This circular-buffer requires a static buffer and a control block (aka handle) assigned. In order to distinguish an empty buffer from a full one, this implementation reserves one byte at the end of the buffer. This means that a buffer should be one byte larger than required by the user.

## Usage 

##### Initialising

Initisalise a buffer with the pointer to a buffer init struct (containing the buffer, size and settings) and a pointer to the handle `CBuffer_Handle_t` struct. A pointer to this structure will be returned on success, or NULL on failure.

```
 
  static uint8_t buffer[BUFF_SIZE+1];
  CBuffer_Handle_t ctrl_blk;
  CBuffer_init_t init = {
    .buffer = buffer, 
    .size = BUFF_SIZE+1, 
  };

  CBuff handle = cbuffer_create(&ctrl_blk, &init);
  
  if(handle == NULL) {
    error_handler("CBuff Create");
  }
```

##### Writing & reading

Write to the cbuffer with `cbuffer_write(handle, &data, &size)` and `cbuffer_read(handle, &data, &size)`. Each takes a constant pointer to the data to read/write, and a constant pointer to the length for the operation. These values contain the actual read/write length at the exit of the function. 


## TODO

- Fix case formatting
- Fix init argument names 
- Write unit tests 




