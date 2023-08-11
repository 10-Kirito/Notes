create definer = root@`%` event refresh_downloadColumn_event on schedule
    every '1' DAY
        starts '2023-05-23 00:00:00'
    enable
    do
    UPDATE users SET freedownload = 2;


