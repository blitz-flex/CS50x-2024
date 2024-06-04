-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Key Informations about crime:
-- the theft took place on July 28, 2021 and that it took place on Humphrey Street

-- Check all tables in database to think where to start
.tables
-- airports              crime_scene_reports   people
-- atm_transactions      flights               phone_calls
-- bakery_security_logs  interviews
-- bank_accounts         passengers


-- details of the theft

SELECT description FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND street = 'Humphrey Street';

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- Check the testimonies of three witnesses

SELECT name, transcript FROM interviews
WHERE day = 28 AND month =7;

-- Ruth: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

-- Eugene: I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- Raymond:  As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Look for ATM atm_transactions on that day

SELECT month, day, bank_accounts.account_number, name transaction_type, amount FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE day = 28 AND month= 7 AND atm_location = 'Leggett Street' AND transaction_type= 'withdraw';

+-------+-----+----------------+------------------+--------+
| month | day | account_number | transaction_type | amount |
+-------+-----+----------------+------------------+--------+
| 7     | 28  | 49610011       | Bruce            | 50     |
| 7     | 28  | 26013199       | Diana            | 35     |
| 7     | 28  | 16153065       | Brooke           | 80     |
| 7     | 28  | 28296815       | Kenny            | 20     |
| 7     | 28  | 25506511       | Iman             | 20     |
| 7     | 28  | 28500762       | Luca             | 48     |
| 7     | 28  | 76054385       | Taylor           | 60     |
| 7     | 28  | 81061156       | Benista          | 30     |
+-------+-----+----------------+------------------+--------+

-- next days destination flights

SELECT flights.id, full_name, city, month, day, hour, minute FROM flights
JOIN airports ON flights.destination_airport_id = airports.id
WHERE day = 29 AND month = 7 ORDER BY hour;

-- +----+-------------------------------------+---------------+-------+-----+------+--------+
-- | id |              full_name              |     city      | month | day | hour | minute |
-- +----+-------------------------------------+---------------+-------+-----+------+--------+
-- | 36 | LaGuardia Airport                   | New York City | 7     | 29  | 8    | 20     |
-- | 43 | O'Hare International Airport        | Chicago       | 7     | 29  | 9    | 30     |
-- | 23 | San Francisco International Airport | San Francisco | 7     | 29  | 12   | 15     |
-- | 53 | Tokyo International Airport         | Tokyo         | 7     | 29  | 15   | 20     |
-- | 18 | Logan International Airport         | Boston        | 7     | 29  | 16   | 0      |
-- +----+-------------------------------------+---------------+-------+-----+------+--------+

-- check passengers

SELECT passengers.passport_number, name, seat name  FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
WHERE flight_id = 36;

+-----------------+--------+------+
| passport_number |  name  | name |
+-----------------+--------+------+
| 7214083635      | Doris  | 2A   |
| 1695452385      | Sofia  | 3B   |
| 5773159633      | Bruce  | 4A   |
| 1540955065      | Edward | 5C   |
| 8294398571      | Kelsey | 6C   |
| 1988161715      | Taylor | 6D   |
| 9878712108      | Kenny  | 7A   |
| 8496433585      | Luca   | 7B   |
+-----------------+--------+------+

-- Comparison query 1: Compare atm withdraw names and passangers name in flight_id = 36

SELECT name FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE day = 28 AND month = 7 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw' AND name IN
    (SELECT name FROM passengers
    JOIN people ON passengers.passport_number = people.passport_number
    WHERE flight_id = 36);


-- The thief one of four
+--------+
|  name  |
+--------+
| Bruce  |
| Kenny  |
| Luca   |
| Taylor |
+--------+

-- Search about the bakery and Check all bakery_security_logs

SELECT month, day, hour, minute, activity, bakery_security_logs.license_plate, name FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE month = 7 AND day = 28 AND hour = 10 AND (minute >= 15 AND  minute <= 25);

+-------+-----+------+--------+----------+---------------+---------+
| month | day | hour | minute | activity | license_plate |  name   |
+-------+-----+------+--------+----------+---------------+---------+
| 7     | 28  | 10   | 16     | exit     | 5P2BI95       | Vanessa |
| 7     | 28  | 10   | 18     | exit     | 94KL13X       | Bruce   |
| 7     | 28  | 10   | 18     | exit     | 6P58WS2       | Barry   |
| 7     | 28  | 10   | 19     | exit     | 4328GD8       | Luca    |
| 7     | 28  | 10   | 20     | exit     | G412CB7       | Sofia   |
| 7     | 28  | 10   | 21     | exit     | L93JTIZ       | Iman    |
| 7     | 28  | 10   | 23     | exit     | 322W7JE       | Diana   |
| 7     | 28  | 10   | 23     | exit     | 0NTHK55       | Kelsey  |
+-------+-----+------+--------+----------+---------------+---------+

-- Comparison query 2: Compare bakery_security_logs licese_plate names and comparison query 1

SELECT name  FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw' AND name IN
    (SELECT name  FROM passengers
    JOIN people ON passengers.passport_number = people.passport_number
    WHERE flight_id = 36)AND name IN
        (SELECT name FROM bakery_security_logs
        JOIN people ON bakery_security_logs.license_plate = people.license_plate
        WHERE month = 7 AND day = 28 AND hour = 10 AND (minute >= 15 AND  minute <= 25));

+-------+
| name  |
+-------+
| Bruce |
| Luca  |
+-------+

--  Check phone calls on that day

SELECT caller, caller.name, receiver, receiver.name, month, day,  duration FROM phone_calls
JOIN people caller ON phone_calls.caller = caller.phone_number
JOIN people receiver ON phone_calls.receiver = receiver.phone_number
WHERE day = 28 AND month = 7 AND duration <=60;


+----------------+---------+----------------+------------+-------+-----+----------+
|     caller     |  name   |    receiver    |    name    | month | day | duration |
+----------------+---------+----------------+------------+-------+-----+----------+
| (130) 555-0289 | Sofia   | (996) 555-8899 | Jack       | 7     | 28  | 51       |
| (499) 555-9472 | Kelsey  | (892) 555-8872 | Larry      | 7     | 28  | 36       |
| (367) 555-5533 | Bruce   | (375) 555-8161 | Robin      | 7     | 28  | 45       |
| (609) 555-5876 | Kathryn | (389) 555-5198 | Luca       | 7     | 28  | 60       |
| (499) 555-9472 | Kelsey  | (717) 555-1342 | Melissa    | 7     | 28  | 50       |
| (286) 555-6063 | Taylor  | (676) 555-6554 | James      | 7     | 28  | 43       |
| (770) 555-1861 | Diana   | (725) 555-3243 | Philip     | 7     | 28  | 49       |
| (031) 555-6622 | Carina  | (910) 555-3251 | Jacqueline | 7     | 28  | 38       |
| (826) 555-1652 | Kenny   | (066) 555-9701 | Doris      | 7     | 28  | 55       |
| (338) 555-6650 | Benista | (704) 555-2131 | Anna       | 7     | 28  | 54       |
+----------------+---------+----------------+------------+-------+-----+----------+

-- Comparison query 3: Compare phone_calls caller names and comparison query 2

SELECT name  FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw' AND name IN
    (SELECT name  FROM passengers
    JOIN people ON passengers.passport_number = people.passport_number
    WHERE flight_id = 36) AND name IN
        (SELECT name FROM bakery_security_logs
        JOIN people ON bakery_security_logs.license_plate = people.license_plate
        WHERE month = 7 AND day = 28 AND hour = 10 AND (minute >= 15 AND  minute <= 25)) AND name IN
            (SELECT name FROM phone_calls
            JOIN people  ON phone_calls.caller = people.phone_number
            WHERE month = 7 AND day = 28 AND duration <=60);


+-------+
| name  |
+-------+
| Bruce |
+-------+
