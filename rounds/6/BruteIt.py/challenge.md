# BruteIt.py

- Published: 07/27/2024 (#5/12 in round)
- Category: Programming/Misc.
- Points: 60
- Author: Vipin

Sometimes, you can’t always reverse engineer it; you might just have to *brute it.*

## Attachments

- [bruteit.py](bruteit.py)

## Hint

This hint costed 10 points.

<details>
<summary>Reveal hint</summary>

The best way to solve is to write a python script that will iterate from 1-999 to find the correct code. It is a waste of time to attempt to de-obfuscate it.

</details>

## Write-up

<details>
<summary>Reveal write-up</summary>

The goal of this challenge is to brute an obfuscated Python file's 3 digit passcode. Since it is obfuscated the goal of the challenge is to brute force it, however some of the people who solve this challenge managed to deobfuscate it.

Below is the intended solve method:

```python
import subprocess

def brute():
    for x in range(1000): # Loop that allows us to brute force the passcode
        code = f"{x:03}" 
        ps = subprocess.run(
            ['python3', 'bruteit/bruteit.py'], # Allows us to run the program
            input=code,
            text=True,
            capture_output=True
        )
        output = ps.stdout.strip()
        
        if 'csd{' in output.lower():  # check in output not ps.stdout
            print("found it!", output, code)
            return code
        else:
            print('.') # if the passcode doesn't print the flag it prints a "."
            continue
    print("not found") # if it doesnt brute force it, it prints not found
    return None

brute()
```

Flag: `csd{S0_8E47_17_jus7_8e47_17}`

</details>

Write-up by [Vipin](https://vipin.xyz)