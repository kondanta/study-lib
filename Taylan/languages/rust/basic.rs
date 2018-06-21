// Testing

fn hello_with_param() {
    let msg = "Param!";
    println!("Hello {}", msg);
}

// fn test_assert() {
//     let num = 5;
//     assert_eq!(num, 10);
// }

fn loop_test() {
    // for i in 0..5 {
    //     if i % 2 == 0 {
    //         println!("Even {}", i);
    //     } else {
    //         println!("Odd {}", i);
    //     }
    // }
    // Interesting way to write above
    for i in 0..5 {
        let val = if i % 2 == 0 { "Even" } else { "Odd" };
        println!("{} is {}", i, val);
    }
}

// Will be improved later
fn adder() {
    //let mut sum = 0.0; gives float to int err.
    let mut sum = 0.0;

    for i in 0..5 {
        //sum += i;
        sum += i as f64; // casting to the float
    }
    println!("Sum {}", sum);
}

fn better_adder(x: f64, y: f64) -> f64 {
    x + y
}

fn adder_with_ref(x: &i32) -> i32 {
    *x + 1
}

fn modifiable_param(x: &mut f64) {
    *x = *x + 3.0;
}

//import and #include< > is
use std::f64::consts;

fn test_constants() {
    let x: f64 = 2.0 * consts::PI;
    let abs_diff = (x.cos() - 1.0).abs();
    assert!(abs_diff < 1e-10);
}

fn arrays(x: &[i32]) -> i32 {
    let mut res = 0;
    for i in 0..x.len() {
        res += x[i];
    }

    res
}

fn use_arr_vals(x: &[i32]) {
    let first = x.get(0).unwrap_or(&1);
    let last = *x.get(4).unwrap_or(&1);
    println!("{:?}", first);
    println!("{:?}", last);
}

fn vectors(slice: &[i32]) {
    println!("{:?}", slice);
}

fn iterators() {
    let mut iter = 0..3;
    assert_eq!(iter.next(), Some(0));
    assert_eq!(iter.next(), Some(1));
}

fn vectors_and_strings() {
    let text = "the red fox and the lazy dog";
    // Underscore means ignore.
    let _words: Vec<&str> = text.split_whitespace().collect();

    let stripped: String = text.chars().filter(|ch| !ch.is_whitespace()).collect();

    println!("{}", stripped);
}

use std::env;
fn read_from_cli() {
    // Reading single arg from cli
    // let first = env::args().nth(1).expect("please supply an argument");
    //let n: i32 = first.parse().expect("not an integer!");
    let args: Vec<String> = env::args().skip(1).collect();
    if args.len() > 0 {
        println!("Provide some args!");
    } else {
        println!("No args");
    }
}

fn switch_case() {
    let multilingual = "Здравствуйте!";
    // Normally its not switch case, but we can use match syntax
    // as if its switch case.
    // What it actually does is, 'is_some().unwrap()
    // But its better than writing is_some explicitly
    match multilingual.find('п') {
        Some(idx) => {
            let hi = &multilingual[idx..];
            println!("Russian hi {}", hi);
        }
        None => println!("couldn't find the greeting, Товарищ"),
    };
}

use std::fs::File;
use std::io;
use std::io::Read;
fn read_from_file_and_error_handling(filename: &str) -> io::Result<String> {
    // requires return to -> Result<String, io::Error>
    // let mut file = match File::open(&filename) {
    //     Ok(f) => f,
    //     Err(e) => return Err(e),
    // };
    // let mut text = String::new();
    // match file.read_to_string(&mut text) {
    //     Ok(_) => Ok(text),
    //     Err(e) => Err(e),
    // }
    // Does the same thing above
    let mut file = File::open(&filename)?;
    let mut text = String::new();
    file.read_to_string(&mut text)?;
    Ok(text)
}

fn main() {
    println!("Hello World!");
    hello_with_param();
    //    test_assert();
    loop_test();
    adder();
    println!("Sum: {:?}", better_adder(10.5, 10.5));
    println!("Sum: {:?}", adder_with_ref(&62));
    let mut val = 9.0;
    // mut should be specified when mutable var passed
    // as an argument
    modifiable_param(&mut val);
    println!("Sum: {}", val);

    test_constants();

    let arr = [10, 20, 30, 40];
    println!("Sum: {:?}", arrays(&arr));
    use_arr_vals(&arr);

    // vector must be mutable.
    let mut vec = Vec::new();
    vec.push(10);
    vec.push(20);
    vec.push(30);

    vectors(&vec);

    iterators();

    vectors_and_strings();

    read_from_cli();

    switch_case();

    let file = env::args().nth(1).expect("please give me filename");
    let text = read_from_file_and_error_handling(&file).expect("Bad file!");

    println!("file had {} bytes", text.len());
}
