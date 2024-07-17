FROM php:8.3.9-cli-alpine

COPY --from=composer:latest /usr/bin/composer /usr/local/bin/composer

ADD --chmod=0755 https://github.com/mlocati/docker-php-extension-installer/releases/latest/download/install-php-extensions /usr/local/bin/

RUN install-php-extensions xdebug-3.3.2

WORKDIR /app

CMD ["php", "entry_point.php"]