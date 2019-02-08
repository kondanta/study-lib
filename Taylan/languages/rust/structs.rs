fn add_tuple(x: f64, y: f64) -> (f64, f64) {
    (x + y, x * y)
}
// derive debug -> tell compiler to create debug info.
#[derive(Debug)]
struct Person {
    fname: String,
    lname: String,
}

// And there's a better way to implement struct

impl Person {
    fn new(first: &str, second: &str) -> Person {
        Person {
            fname: first.to_string(),
            lname: second.to_string(),
        }
    }
    // &self itself a param with the struct
    fn full_name(&self) -> String {
        format!("{} {}", self.fname, self.lname)
    }

    fn set_first_name(&mut self, name: &str) {
        self.fname = name.to_string();
    }
}

// Compiler explains how to use generic, with instructions.
// This function came here from fn generic<T>(x: T) -> T {}
fn generic<T>(x: T) -> T::Output
where
    T: std::ops::Mul + Copy,
{
    x * x
}

type NodeBox = Option<Box<Node>>;

#[derive(Debug)]
struct Node {
    payload: String,
    left: NodeBox,
    right: NodeBox,
}

impl Node {
    fn new(s: &str) -> Node {
        Node {
            payload: s.to_string(),
            left: None,
            right: None,
        }
    }
    fn boxer(node: Node) -> NodeBox {
        Some(Box::new(node))
    }
    fn set_left(&mut self, node: Node) {
        self.left = Self::boxer(node);
    }
    fn set_right(&mut self, node: Node) {
        self.right = Self::boxer(node);
    }
}

#[derive(Debug)]
// 'a indicates the life time. Compiler helps it
struct Test<'a> {
    s: &'a str,
}

trait Show {
    fn show(&self) -> String;
}

impl Show for i32 {
    fn show(&self) -> String {
        format!("Four-byte Signed {}", self)
    }
}

fn dmp<T>(value: &T)
where
    T: std::fmt::Debug,
{
    println!("Val is {:?}", value);
}

fn main() {
    let t = add_tuple(2.0, 3.0);
    println!("t: {:?}", t);

    // Struct test
    let p = Person {
        fname: "test".to_string(),
        lname: "nmane".to_string(),
    };

    println!("fname {}, lname {}", p.fname, p.lname);

    // Impl person
    // Its mut bc i've changed the first name below.
    let mut p2 = Person::new("A", "B");

    println!("fname {}, lname {}", p2.fname, p2.lname);
    p2.set_first_name("Mamudu");
    println!("Full name: {:?}", p2.full_name());
    println!("{:?}", p);

    println!("{:?}", generic(42));

    // Closures! => Anounymous functions.
    // Also they seem to be type agnostic.
    let f = |x| x * x;
    println!("{:?}", f(2));

    let mut root = Node::new("root");
    root.set_left(Node::new("left"));
    root.set_right(Node::new("right"));

    println!("arr {:#?}", root);

    //TODO:: continue from generic structs.
    // 16.1.19
    let a = "Hmm".to_string();
    let t1 = Test { s: &a };
    println!("{:?}", t1);
    // using trait
    println!("show {}", 42.show());

    // Just for testing something
    // addin _ infront of a variable marks it
    // will not be used
    let _child = std::process::Command::new("/bin/cat")
        .arg("languages.org")
        .current_dir("~/documents/notes")
        .stdout(std::process::Stdio::piped())
        .spawn();
    // Generic functions
    dmp(&42.0);
}
