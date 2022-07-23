# memscan
**Feature-rich** **C99** library for memory scanning purposes, designed for **Windows** running machines, meant to work on both **32-bit** and **64-bit** portable executables.

**memscan** has a **modern C++** wrapper which abstracts the **C** contents in an user-friendly way. To look at the **C** example, press [here](./src/test.c), and, for the **C++** example, press [here](./src/test.cpp).

### ✔ Features
- 🚶 Follow system
    <details>

    - - -
    It is an internal concept which is exposed to every of the following memscan **features**.
    - - - 
  
    - It expects a base address, bounds and a find sequence.
    - Find sequences can be made of:
      - A bytecode-style string:
        - Example: ``"AA BB CC DD EE FF"``
          - This is converted back to a byte array with a size at run-time.
      - **OR**, byte array and it's size
        - Example: ``{0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}, 6``
      - And, universally:
        - N-th match:
          - Sequences may repeat within the specified range, so you can choose which match you want to select,
          - Matches start at 0, implying the first match.
        - Direction:
          - You can go either backwards, or forwards, within the specified bounds, starting from the base address.
    - Invalid inputs will be reflected in the return with the status variable. This carries to the user-level return.

    </details>

- 🔎 Multi-paradigm pattern-scanning
  <details>
  
  - It expects bounds, a pattern sequence and, optionally, a find sequence.
  - Pattern sequences can be made of:
      - A bytecode-style string:
        - Example: `"AA BB CC DD EE FF"`
      - **OR**, a byte array and it's size
        - Example: ``{0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}, 6``
      - Both of the aforementioned can contain a preset symbol to signal that a mismatch at said position is allowed. It is set [here](./src/memscan/memscan.h).
      - And, universally:
        - N-th match:
          - Sequences may repeat within the specified range, so you can choose which match you want to select,
          - Matches start at 0, implying the first match.
  - Refer to **Follow system** to see find sequences.
  - Every combination of the aforementioned is possible in the user-level API.
  - The result of this process carries an address depending on the success of the process and a status. For documentation on the status, refer to [this](./src/memscan/memscan.h) file.
  
  </details>
  
- ❌ Cross-reference resolver
  <details>
  
  - It expects bounds, either a base address or content, prompt to whether there should be an endianness swap, N-th match, based on which method you choose and, optionally, a find sequence.
  - Refer to **Follow system** to see find sequences.
  - Can resolve references from a given input, or, resolve references at the address where they're represented:
    - An example for resolving references from a given input is inputting the following: ``0xAABBCCDD``.
      - We assume this is a pointer which we can resolve. When represented in memory, it'll have it's endianness swapped, so it'll look like ``0xDDCCBBAA``, therefore, we will ask for an endianness swap,
      - Then, for some reason, want to find the first instance where the contents at the pointer is referenced, so, we will input ``0`` for the N-th match.
    - We can also input the address where a pointer is referenced by choosing the right method:
      - If the contents at our address look like this sequence: ``8B 4D ? ? ? ?``:
        - We'll have to add '`2'` to the address (to skip over the ``8B 4D`` bytes),
        - Then, we'll have to prompt an endianness swap,
        - Then, for some reason, want to find the first instance where the contents at the address' pointer is referenced so, we will input ``0`` for the N-th match.
  - Refer to **Follow system** to see find sequences.
  - The result of this process carries an address depending on the success of the process and a status. For documentation on the status, refer to [this](./src/memscan/memscan.h) file.
  
  </details>
  
- 🗒️ String resolver
  <details>
  
  - - -
  This component was built off the cross-reference resolver system.
  - - -
  
  - It expects bounds, a (compile-time) string, it's size, N-th match and, optionally, a find sequence.
  - Refer to **Follow system** to see find sequences.
  - The result of this process carries an address depending on the success of the process and a status. For documentation on the status, refer to [this](./src/memscan/memscan.h) file.
    - If the process was succesful, the address will be a pointer to the N-th match of the string.
  
  </details>

- 🤷 Scalable
  <details>
  
  - This project is designed to operate under any reasonable circumstance. This can be used alongside DLL-injection, or on copied memory buffers.

  </details>
  
### 📚 Internal documentation
- The user-level API has up-to-date, Doxygen-compliant documentation, which, in most IDEs, should be displayed on hover.
- There's also implementation documentation which you can see [here](./src/memscan/memscan.c).

### 📈 Progression
- To do:
  - [x] ⚔️ C++ wrapper
  - [ ] 🦾 CMake package
  - [ ] 🧪 Standard tests
  - [ ] 🤝 Multi-platform support

### ⚖️ License
I couldn't care less.
