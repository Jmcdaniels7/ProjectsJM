insert into customer (f_name, l_name, age, gender, house_at_hogwarts) values("Harry", "Potter", "14", "Male", "Gryffindor");
insert into customer (f_name, l_name, age, gender, house_at_hogwarts) values("Hermoine", "Granger", "14", "Female", "Gryffindor");
insert into customer (f_name, l_name, age, gender, house_at_hogwarts) values("Ronald", "Weasley", "14", "Male", "Gryffindor");
insert into customer (f_name, l_name, age, gender, house_at_hogwarts) values("Draco", "Malfoy", "14", "Male", "Slytherin");
insert into customer (f_name, l_name, age, gender, house_at_hogwarts) values("Cedric", "Diggory", "17", "Male", "HufflePuff");
insert into customer (f_name, l_name, age, gender, house_at_hogwarts) values("John", "Rogers", "14", "Male", "Gryffindor");
insert into customer (f_name, l_name, age, gender, house_at_hogwarts) values("Helga", "Ashwinder", "14", "Female", "HufflePuff");
insert into customer (f_name, l_name, age, gender, house_at_hogwarts) values("Peter", "Malark", "17", "Male", "Gryffindor");
insert into customer (f_name, l_name, age, gender, house_at_hogwarts) values("Derek", "Lastrange", "12", "Male", "Slytherin");
insert into customer (f_name, l_name, age, gender, house_at_hogwarts) values("Carl", "Black", "12", "Male", "Ravenclaw");

insert into items (item_type, item_price, item_description) values("Scroll", "25", "Scroll of Fire Spell");
insert into items (item_type, item_price, item_description) values("Potion", "80", "Potion of Healing");
insert into items (item_type, item_price, item_description) values("Broom Upgrade", "250", "Upgrades speed");
insert into items (item_type, item_price, item_description) values("Broom", "2000", "Hazelnut Broom of Mediocre Speed");
insert into items (item_type, item_price, item_description) values("Broom", "70000", "DragonHeart broom of Grand Speed");

insert into visits (customer_ID, clock_in, clock_out, date) values("1", "1:30pm", "2:00pm", "1994-03-22");
insert into visits (customer_ID, clock_in, clock_out, date) values("4", "9:20pm", "9:45pm", "1994-03-22");
insert into visits (customer_ID, clock_in, clock_out, date) values("2", "9:12am", "9:30am", "1994-03-23");
insert into visits (customer_ID, clock_in, clock_out, date) values("5", "9:25am", "9:45am", "1994-03-23");
insert into visits (customer_ID, clock_in, clock_out, date) values("3", "9:27am", "9:35am", "1994-03-23");

insert into purchase (customer_ID, purchase_amount, date) values("1", "25", "1994-03-22");
insert into purchase (customer_ID, purchase_amount, date) values("4", "70000", "1994-03-22");
insert into purchase (customer_ID, purchase_amount, date) values("2", "80", "1994-03-23");
insert into purchase (customer_ID, purchase_amount, date) values("5", "1500", "1994-03-23");
insert into purchase (customer_ID, purchase_amount, date) values("3", "25", "1994-03-23");

insert into item_sales (purchase_ID, item_ID) values("1", "1");
insert into item_sales (purchase_ID, item_ID) values("2", "5");
insert into item_sales (purchase_ID, item_ID) values("3", "2");
insert into item_sales (purchase_ID, item_ID) values("4", "3");
insert into item_sales (purchase_ID, item_ID) values("5", "1");




