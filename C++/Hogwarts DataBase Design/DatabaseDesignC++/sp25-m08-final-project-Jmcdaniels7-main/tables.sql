CREATE TABLE customer (
    customer_ID integer NOT NULL PRIMARY KEY,
    f_name text NOT NULL,
    l_name text NOT NULL,
    age integer NOT NULL,
    gender text NOT NULL,
    house_at_hogwarts text NOT NULL
);

CREATE TABLE purchase (
    purchase_ID integer NOT NULL PRIMARY KEY,
    customer_ID integer REFERENCES customer(customer_id),
    purchase_amount text NOT NULL,
    date datetime NOT NULL
);

CREATE TABLE visits (
    visit_ID integer NOT NULL PRIMARY KEY,
    customer_ID integer REFERENCES customer(customer_id),
    clock_in datetime NOT NULL,
    clock_out datetime NULL,
    date datetime NOT NULL
);

CREATE TABLE items (
    item_ID integer NOT NULL PRIMARY KEY,
    item_price text NOT NULL,
    item_description text NOT NULL,
    item_type text NOT NULL
);

CREATE TABLE item_sales (
    sale_ID integer NOT NULL PRIMARY KEY,
    purchase_ID integer REFERENCES purchase(purchase_ID),
    item_ID integer REFERENCES items(item_ID)
);
