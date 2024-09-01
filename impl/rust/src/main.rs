use rand::Rng;

pub struct Ipv6Prefix {
    addr: std::net::Ipv6Addr,
    prefix_len: u8,
}

impl std::fmt::Display for Ipv6Prefix {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "{}/{}", self.addr, self.prefix_len)
    }
}

pub fn make_ula_prefix() -> Ipv6Prefix {
    let mut rng = rand::thread_rng();
    let ula = std::net::Ipv6Addr::new(
        0xfd00 | (rng.gen::<u8>() as u16),
        rng.gen::<u16>(),
        rng.gen::<u16>(),
        0x0,
        0x0,
        0x0,
        0x0,
        0x0,
    );
    Ipv6Prefix{
        addr: ula,
        prefix_len: 48,
    }
}

fn main() {
    println!("{}", make_ula_prefix());
}
