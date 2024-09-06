# Animal Pointers

- Published: 08/25/2024 (#11/12 in round)
- Category: Webex, Programming
- Points: 30
- Author: Kshau

Start by sending animal header as "lion". This will give you the name of another animal, which you must do the same with. Repeat.

## Attachments

- [http://3.82.204.187/animal-pointers/animal](http://3.82.204.187/animal-pointers/animal)

## Hint

N/A

## Write-up

<details>
<summary>Reveal write-up</summary>

Simple challenge where the user needs to submit the header lion and then the page provides us with another header to put as the animal header.

Below is an example solve script to do this:

```python
import requests

url = "http://3.82.204.187/animal-pointers/animal"
starting = "lion"

while True:
    headers = {
        "animal": starting  
    }
    response = requests.get(url, headers=headers)
    starting = response.text 
    print(response.text)


Flag: ```csd{XL20aA6CLOlRAXe6dyTMj}```


</details>

Write-up by [Vipin](https://vipin.xyz)