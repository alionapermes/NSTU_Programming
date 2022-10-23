DROP TABLE IF EXISTS "box";
DROP TABLE IF EXISTS "rack";

CREATE TABLE "box" (
    id    SERIAL,
    items VARCHAR[],

    PRIMARY KEY (id)
);

CREATE TABLE "rack" (
    id        SERIAL,
    box_id    INTEGER UNIQUE,
    positions INTEGER[][],

    PRIMARY KEY (id)
);

INSERT INTO
    "box"
    (items)
VALUES
    ('{"one", "two", "three"}'),
    ('{"abo", "buba"}'),
    ('{"five", "six", "seven"}'),
    ('{"eight", "nine"}'),
    ('{"aaaa", "bbbb", "cccc"}'),
    ('{"last", "row"}');

INSERT INTO
    "rack"
    (box_id, positions)
VALUES
    (1, '{{0, 0}, {0, 1}}'),
    (2, '{{0, 2}, {0, 3}, {0, 4}}'),
    (3, '{{1, 0}, {1, 1}, {1, 2}}'),
    (4, '{{2, 0}, {2, 1}}'),
    (5, '{{3, 0}, {3, 1}, {3, 2}}'),
    (6, '{{4, 0}, {4, 1}, {4, 2}}');

SELECT
    id, items[3]
FROM
    "box"
WHERE
    items[3] IS NOT NULL;

SELECT
    id, positions[1:2]
FROM
    "rack";

SELECT
    id, ARRAY_DIMS(positions)
FROM
    "rack";

UPDATE
    "box"
SET
    items[1] = 'the_last'
WHERE
    id = 6;

UPDATE
    "box"
SET
    items[1:2] = '{"biba", "boba"}'
WHERE
    id = 2;

UPDATE
    "box"
SET
    items = '{"the", "last", "row"}'
WHERE
    id = 6;

SELECT
    "rack".*,
    "box".items AS box_items
FROM
    "rack"
LEFT JOIN
    "box"
    ON "box".id = "rack".box_id;

