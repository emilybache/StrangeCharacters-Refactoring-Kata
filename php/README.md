For general instructions see the README.md file in the root directory.

To run the php version you'll need:

* PHP >= 8.3
  * ext-readline
* Composer

If you have docker available, you can build the image using:

```bash
docker build . -t strange_characters
```

To run the tests use:

```bash
 docker run --rm -v $(pwd):/app -it strange_characters vendor/phpunit/phpunit/phpunit
 ```
