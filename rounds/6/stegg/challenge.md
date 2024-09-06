# stegg

- Published: 07/24/2024 (#2/12 in round)
- Category: Forensics
- Points: 30
- Author: Vipin

as for practicality... half of all easy thm machines have steg for some reason

## Attachments

- [chall.zip](chall.zip)

## Hint

This hint costed 10 points.

<details>
<summary>Reveal hint</summary>

If we use StegHide, we realize it's password protected. We need to find a fast tool to crack the StegHide password...

Tip: Don't use StegCracker at all when attempting to solve the challenge, it is painfully slow.

</details>

## Write-up

<details>
<summary>Reveal write-up</summary>

A somewhat guessy challenge. To solve this challenge, we need to install ***Stegseek***. ***Stegseek*** is an incredibly fast Steghide Password Cracker. Below is the intended solve steps.

```bash
❯ stegseek --crack egg.jpg -wl /home/vipin/ctf/wordlists/pwdcracking/rockyou.txt
StegSeek 0.6 - https://github.com/RickdeJager/StegSeek

[i] Found passphrase: "murrayfield1990"
[i] Original filename: "flag.txt".
[i] Extracting to "egg.jpg.out".

❯ cat flag.txt
csd{4lL_H41L_7HE_e99_16X2XU}
```

Flag: `csd{4lL_H41L_7HE_e99_16X2XU}`

</details>

Write-up by [Vipin](https://vipin.xyz)