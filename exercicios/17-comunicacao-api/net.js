const request = require("request");
const configuracao = require("./config");
const api = configuracao.api;

/**
 * Atualiza informação do sensor
 * @param {number} id Id do Sensor
 * @param {object} dados dados a atualizar
 * @param {function} callback função de retorno
 */
function atualizar(id, dados, callback) {
    const endpointUpdateSensor = api + "/api/Sensor/" + id;
    request.put(endpointUpdateSensor, {
        json: true,
        body: dados
    }, function(error, res, body) {
        callback(error, body);
    });
}

function obterId(callback) {
    // via POST /api/Sensor/
    request.post(api + "/api/Sensor", {
        json: true,
        body: {}
    }, function(erro, res, body) {
        callback(erro, body.id);
    });
}

exports.atualizar = atualizar;
exports.obterId = obterId;