// importing the necessary modules
const path = require('path');
const cnf = require(path.join(__dirname, '..', '..', 'Config.js'));
const express = require('express');
const router = express.Router();

router.post('/server_data.php', function (req, res) {
    const content = `server|${cnf.server_ip}
port|${cnf.server_port}
type|1
#maint|lorem ipsum dolor sit amet
loginurl|${cnf.loginurl}
meta|${cnf.meta}
RTENDMARKERBS1001`;
    res.send(content);
})

// exporting the router
module.exports = router;